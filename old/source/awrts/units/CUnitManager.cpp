#include <cstring>

#include <hrengin/platform/time.h>

#include <hrengin/core/paths.h>
#include <hrengin/io/IReadFile.h>
#include <hrengin/io/IBufferedStream.h>
#include <hrengin/hdf/IHDFParser.h>

#include <hrengin/game/IEventManager.h>
#include <hrengin/game/IEntityManager.h>

#include <hrengin/scene/ISceneManager.h>
#include <hrengin/scene/IVisNode.h>

#include <Physics.h>

#include "CUnit.h"
#include <units/ILocomotor.h>
#include <units/CLocomotor.h>
#include "../CDebris.h"
#include "UnitType.h"
#include "CUnitManager.h"
#include "../ai/CNavigatorGround.h"
#include "../ai/CNavigatorWheeled.h"
#include <ai/CGhostNavigator.h>

namespace hrengin {
namespace awrts {

CUnitManager::CUnitManager(graphics::ISceneManager* sceneManager, 
	physics::IPhysicsManager* physicsManager,
	physics::IPhysicsWorld* physicsWorld,
	IEntityManager* entityManager,
	IEventManager* eventManager)
: scnmgr_(sceneManager), phymgr_(physicsManager), physWorld_(physicsWorld),
	entmgr_(entityManager), evtmgr_(eventManager)
{

}

CUnit& CUnitManager::createUnit(hrengin::u32 id, Vector3d<f32> position, hrengin::f32 facing)
{
	UnitType unitType = unitTypes_[id];

	graphics::IVisNode* unitVisual = scnmgr_->createMeshSceneNode(unitType.visualModelName);

	physics::IRigidBody::RigidBodyConstructionInfo rbInfo;

	rbInfo.mass = 0.0f;
	rbInfo.position = position;
	
	physics::IRigidBody* rb = phymgr_->createBody(unitType.guiSelectionShapeId, rbInfo);
	physWorld_->addBody(rb,physics::CollisionFilter(COL_UNIT, COL_GROUND | COL_UNIT | COL_DEBRIS));

#if 0
	physics::ICollisionObject* rb = phymgr_->createPhantom(unitType.guiSelectionShapeId);
	physWorld_->addObject(rb,physics::CollisionFilter(COL_UNIT, COL_GROUND | COL_UNIT | COL_DEBRIS));
#endif

	CUnit* unit = new CUnit(this, unitType, unitVisual, rb, evtmgr_);
	
	rb->setPointer(unit);
	unitVisual->setParentEntity(unit);
	entmgr_->addEntity(unit);
	
	ILocomotor* locomotor = new CLocomotor(unit, unitType);
	hrengin::ai::IBaseNavigator* navigator;

	switch (unitType.movementType) {
	case UnitType::UM_WHEELED:
		navigator = new CNavigatorWheeled(unit, locomotor, physWorld_);
		break;
	case UnitType::UM_GROUND:
	default:
		navigator = new CNavigatorGround(unit, locomotor, physWorld_);
	}

	unit->setPosition(position);
	unit->setFacing(facing);
	unit->sync();

	units_.push_back(unit);

	return *unit;
};

char* stringToChar(std::string source)
{
	char* dest = new char[source.size() + 1];
	strcpy(dest, source.c_str());
	return dest;
}

bool parseUnitType(hdf::IHDFParser* hdf, std::string node, UnitType& utype, physics::IPhysicsManager* phymgr)
{
	while(hdf->read()) {
		hdf::HdfObjectType type = hdf->getObjectType();
		std::string name;
		std::string temp;

		switch(type) {
		case hdf::HDF_OBJ_NODE:
			hdf->getObjectName(name);
			parseUnitType(hdf, name, utype, phymgr);
			break;
		case hdf::HDF_OBJ_VAL:
			hdf->getObjectName(name);
			if(name == "id" && node == "unit") {
				hdf->readString(temp);
				utype.id = (temp.c_str()[0] << 24) +
				(temp.c_str()[1] << 16) + 
				(temp.c_str()[2] << 8) + 
				temp.c_str()[3];
			} else if(name == "unit_name" && node == "text") {
				hdf->readString(temp);
				utype.textUnitName = stringToChar(temp);
			} else if(name == "description" && node == "text") {
				hdf->readString(temp);
				utype.textDescription = stringToChar(temp);
			} else if(name == "model_name" && node == "visual") {
				hdf->readString(temp);
				utype.visualModelName = stringToChar(temp);
			} else if(name == "phys_shape" && node == "physics") {
				hdf->readString(temp);
				utype.guiSelectionShapeId = phymgr->loadModel(temp.c_str());
			} else if(name == "type" && node == "movement") {
				hdf->readString(temp);
				if(temp == "hover") {
					utype.movementType = UnitType::UM_HOVER;
				} else if(temp == "ground") {
					utype.movementType = UnitType::UM_GROUND;
				} else if(temp == "wheeled") {
					utype.movementType = UnitType::UM_WHEELED;
				} else if(temp == "tracked") {
					utype.movementType = UnitType::UM_TRACKED;
				}
			} else if(name == "height" && node == "movement") {
				hdf->readFloat(utype.movementHeight);
			} else if(name == "speed" && node == "movement") {
				hdf->readFloat(utype.movementSpeed);
			} else if(name == "acceleration" && node == "movement") {
				hdf->readFloat(utype.movementAcceleration);
			} else if(name == "turn_speed" && node == "movement") {
				hdf->readFloat(utype.movementTurnSpeed);
			} else if(name == "can_reverse" && node == "movement") {
				hdf->readBool(utype.movementCanReverse);
			} else if(name == "hitpoints" && node == "combat") {
				hdf->readFloat(utype.statsHitPointsMax);
			} else {
				hdf->error(hdf::HDF_LOG_ERROR, "unknown object: " + name + ", in node " + node);
				return false;
			}
			break;
		case hdf::HDF_OBJ_NODE_END:
			return true;
			break;
		case hdf::HDF_OBJ_NULL:
		default:
			return false;
		}
	}

	return true;
}

void CUnitManager::loadUnitTypes()
{
	io::IReadFile* file = io::openReadFile(io::datapath + "objects/unit_types.hdf");
	io::IBufferedStream* stream = io::createBufferedStream(file);
	hdf::IHDFParser* hdf = hdf::createHDFParser(stream);

	while(hdf->read()) {
		if(hdf->getObjectType() == hdf::HDF_OBJ_NODE) {
			std::string name;
			hdf->getObjectName(name);

			// skip unknown node
			if(name != "unit") {
				hdf->error(hdf::HDF_LOG_WARNING, "unknown node: " + name);
				hdf->skipNode();
			} else {
				UnitType utype;
				bool success = parseUnitType(hdf, name, utype, phymgr_);
				if(success) {
					addType(utype);
				}
			}
		} else {
			break;
		}
	}
	
	delete hdf;
	delete stream;
	delete file;
}

}
} // namespace hrengin
