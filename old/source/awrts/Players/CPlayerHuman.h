#ifndef _awrts_CPlayerHuman_
#define _awrts_CPlayerHuman_

#include <hrengin/common/Vector3d.h>
#include <hrengin/common/Line3d.h>

#include <hrengin/scene/ISceneManager.h>
#include <hrengin/scene/ICameraNode.h>

#include <hrengin/gui/IUserInputReceiver.h>
#include <hrengin/gui/IInputManager.h>

#include <hrengin/game/IEntityManager.h>
#include <hrengin/game/IEventManager.h>

#include <Physics.h>

#include "../units/CUnit.h"
#include "../units/CUnitGroup.h"

#include "IPlayer.h"

namespace hrengin {
namespace awrts {

// human-controlled human
class CPlayerHuman : public IPlayer, public IUserInputReceiver {
public:
	CPlayerHuman(scene::ISceneManager* sceneManager,
		CUnitManager* unitManager,
		physics::IPhysicsWorld* physicsWorld);
	//void ApplyCamera();
	
	virtual bool onUserInput(hrengin::gui::InputEvent input);

	virtual bool isEnabled()
	{
		return !PlayerInputDisabled;
	}
	
	virtual bool Sync() 
	{
		//mPosition = mPOV->mPosition;
		return false;
	}
private:
	IEntityManager* entmgr_;
	scene::ISceneManager* scnmgr_;
	CUnitManager* unitmgr_;
	//physics::IPhysicsManager* phymgr_;
	physics::IPhysicsWorld* physWorld_;

	CUnit* getUnitFromRay(Line3d<f32> ray);
	virtual void processMouseInput(hrengin::gui::InputEvent input);
private:
	bool PlayerInputDisabled;


	hrengin::u32 mSlot;

	hrengin::scene::ICameraNode* povCamera_;

	
	CUnit* tmpSelUnit_;
	
	CUnitGroup selection_;
};

}
}

#endif//_awrts_CPlayerHuman_
