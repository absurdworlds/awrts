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

}
} // namespace hrengin
