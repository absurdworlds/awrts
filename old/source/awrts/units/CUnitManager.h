#ifndef __H_INCLUDED__AWRTS_CUnitManager
#define __H_INCLUDED__AWRTS_CUnitManager

#include <vector>
#include <unordered_map>

#include <hrengin/common/types.h>

#include "UnitType.h"
#include "CUnit.h"

namespace hrengin {
class IEntityManager;
class IEventManager;
namespace graphics {
class ISceneManager;
}
namespace physics {
class IPhysicsManager;
class IPhysicsWorld;
}
namespace awrts {

class CUnit;
class CUnitType;

class CUnitManager {
public:
	CUnitManager(graphics::ISceneManager* sceneManager, 
		physics::IPhysicsManager* physicsManager,
		physics::IPhysicsWorld* physicsWorld,
		IEntityManager* entityManager,
		IEventManager* eventManager);

	CUnit& createUnit(hrengin::u32 id, Vector3d<f32>position, hrengin::f32 facing=0.0f);
	size_t getUnitCount()
	{
		return units_.size();
	};

	void loadUnitTypes();
	std::unordered_map<hrengin::u32,UnitType> unitTypes_;
private:
	std::vector<CUnit*> units_;

	graphics::ISceneManager* scnmgr_;
	physics::IPhysicsManager* phymgr_;
	physics::IPhysicsWorld* physWorld_;
public:
	IEntityManager* entmgr_;
	IEventManager* evtmgr_;
};

}
}

#endif//__H_INCLUDED__AWRTS_CUnitManager
