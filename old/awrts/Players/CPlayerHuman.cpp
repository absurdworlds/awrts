
#include <random>
#include <string>

#include <hrengin/common/Vector3d.h>
#include <hrengin/core/ILogger.h>
#include <hrengin/core/ISettingsManager.h>

#include <hrengin/physics/IPhysicsManager.h>
#include <hrengin/physics/ICollisionObject.h>

#include <hrengin/sound/ISoundManager.h>

#include <units/CUnit.h>
#include <units/CUnitManager.h>

#include "CPlayerHuman.h"

#include "../awrts.h"
#include "../CDebris.h"

namespace hrengin {
namespace awrts {

CPlayerHuman::CPlayerHuman(graphics::ISceneManager* sceneManager,
		CUnitManager* unitManager,
		physics::IPhysicsWorld* physicsWorld)
	: PlayerInputDisabled(false), physWorld_(physicsWorld), scnmgr_(sceneManager),
	unitmgr_(unitManager), tmpSelUnit_(0), entmgr_(unitManager->entmgr_)
{
}

CUnit* CPlayerHuman::getUnitFromRay(Line3d<f32> ray)
{
	physics::IClosestHitCallback callback;

	callback.collFilter.group = COL_UNIT;
	callback.collFilter.mask = COL_UNIT;

	// todo: intentionally swap end and start to make funny bugs	
	physWorld_->castRay(ray.start, ray.end, &callback);

	if(!callback.hasHit()) {
		return 0;
	}
	
	physics::ICollisionObject const* rayHit = callback.collObject;

	hrengin::IBaseEntity* foundEntity = reinterpret_cast<IBaseEntity*>(rayHit->getPointer());

	if(foundEntity->getEntityIdentifier() != 'unit') {
		return 0;
	}

	return static_cast<CUnit*>(foundEntity);
}

void playUnitResponce(u32 unitId, bool order)
{
	std::string suffix = order ? "yes" : "ready";

	std::string sound;

	if(unitId == 'Stnk') {
		sound = "generic2_" + suffix + "01.wav";
	} else {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, 2);
		sound = "generic_"  + suffix + "0"+std::to_string(dis(gen))+".wav";
	}
	
	sound::getSoundManager().playSound(sound.c_str());
}

void CPlayerHuman::processMouseInput(gui::InputEvent input)
{
	i32 X = input.mouse.X;
	i32 Y = input.mouse.Y;

	switch(input.mouse.event) {
	case gui::MouseEventType::LButtonDown:
		break;
	case gui::MouseEventType::LButtonUp:
		Line3d<f32> ray = povCamera_->getRayFromScreen(X, Y);
		CUnit* rayHit = getUnitFromRay(ray);
		unsigned char unitId[5];

		
		if(rayHit) {
			getStringFromUnitId(rayHit->getUnitTypeID(),unitId);

			printf("%s: Standing by\n", unitId);

			playUnitResponce(rayHit->getUnitTypeID(), false);

			tmpSelUnit_ = rayHit;
		} else if(tmpSelUnit_) {
			getStringFromUnitId(tmpSelUnit_->getUnitTypeID(),unitId);

			printf("%s: Affirmative!\n", unitId);

			physics::IClosestHitCallback callback;
			callback.collFilter.group = COL_STATIC;
			callback.collFilter.mask = COL_STATIC;

			Line3d<f32> ray = povCamera_->getRayFromScreen(X,Y);
			physWorld_->castRay(ray.start,ray.end,&callback);

			Vector3d<f32> pos = callback.hitPoint;

			tmpSelUnit_->issuePointOrder(ORDER_MOVE, pos);
			
			playUnitResponce(tmpSelUnit_->getUnitTypeID(), true);
			//UnitType utype = unitmgr_->unitTypes_[tmpSelUnit_->getUnitTypeID()];
		}
		break;
	}
}

bool CPlayerHuman::onUserInput(hrengin::gui::InputEvent input)
{
	static double c4islo = 0;
	static bool hovering_muthafcuka;
	static i32 element;
	
	if(input.type == gui::InputEventType::GUIEvent) {
		if(input.gui.event == gui::GUIEventType::ElementHovered) {
			hovering_muthafcuka = true;
			if(input.gui.caller != -1) {
				element = input.gui.caller;
			}
		} else if(input.gui.event == gui::GUIEventType::ElementLeft) {
			hovering_muthafcuka = false;
		} else if(input.gui.event == gui::GUIEventType::ElementClosed) {
			if(input.gui.caller == element) {
				hovering_muthafcuka = false;
			}
		}
		return false;
	}

	if(hovering_muthafcuka) {
		return false;
	}

	static i32 X;
	static i32 Y;

	if(input.type == gui::InputEventType::MouseEvent) {
		X = input.mouse.X;
		Y = input.mouse.Y;

		processMouseInput(input);
	} else if (input.type == gui::InputEventType::KeyboardEvent) {
		static int numbers = 0;
		//hrengin::CLogger::log("knopkodoska input " + std::to_string(app.encore->GetTime()) + "\n");
		if(input.key.keyCode == irr::KEY_KEY_I && input.key.pressedDown)
		{
			hrengin::base::line3df ray = povCamera_->castRayFromScreen(X,Y);
			CUnit* rayHit = getUnitFromRay(ray);
			if(!rayHit)
			{
				CUnitManager& umgr = app.unitmgr;
				static unsigned int lastId = 0;
				unsigned int unitId;
				int i = 0;
				for(std::unordered_map<hrengin::u32,UnitType>::iterator it = umgr.unitTypes_.begin();
					it != umgr.unitTypes_.end();
					++it,++i) {
					if(lastId % umgr.unitTypes_.size() == i) {
						unitId = (*it).second.id;
					}
				}

				Vector3d<f32>pos = povCamera_->__tempGetRayHitPlaneCoords(X,Y);
				unitmgr_->createUnit(unitId,pos);

				++ lastId;
			}
		} else if (input.key.keyCode == irr::KEY_KEY_U && input.key.pressedDown) {
			hrengin::getLogger().push("DEBUG:");
			hrengin::getLogger().push(std::to_string(unitmgr_->getUnitCount()));


			hrengin::getLogger().push(hrengin::endl);
		} else if (input.key.keyCode == irr::KEY_KEY_P && input.key.pressedDown) {
			app.profiling = !app.profiling;
			getLogger().push("DEBUG: Profiling =");
			getLogger().push(std::to_string(app.profiling));
			getLogger().push(hrengin::endl);
		} else if (input.key.keyCode == hrengin::KEY_KEY_S && input.key.pressedDown) {
			if(tmpSelUnit_) {
				tmpSelUnit_->issueImmediateOrder(ORDER_STOP);
			}
		} else if (((input.key.keyCode >= hrengin::KEY_KEY_0 && input.key.keyCode <= hrengin::KEY_KEY_9) 
		|| input.key.keyCode == hrengin::KEY_TAB) 
		&& input.key.pressedDown) {
			if(input.key.keyCode == hrengin::KEY_TAB) {
				c4islo = 0.0;
			}
			else {
				c4islo *= 10;
				c4islo += (input.key.keyCode - hrengin::KEY_KEY_0);
			}

			printf("c4islo = %f\n",c4islo);
		} else if (input.key.keyCode == hrengin::KEY_KEY_D && input.key.pressedDown) {

			//new CDebris(pos,phymgr_,scnmgr_,entmgr_ );
		} else if (input.key.keyCode == hrengin::KEY_KEY_G && input.key.pressedDown) {
			i32 debugMode = 0;
			core::getSettingsManager().getValue("debugmode",debugMode);
			if(debugMode == 100) {
				core::getSettingsManager().setValue("debugmode",0);
			} else {
				core::getSettingsManager().setValue("debugmode",100);
			}
			core::getSettingsManager().getValue("debugmode",debugMode);
		}
	}


	return false;
}

}
}
