#ifndef _awrts_Physics_
#define _awrts_Physics_

#include <hrengin/common/types.h>
#include <hrengin/common/macro.h>

#include <hrengin/physics/IPhysicsManager.h>
#include <hrengin/physics/IPhysicsWorld.h>

#include <hrengin/physics/ICollisionPhantom.h>
#include <hrengin/physics/IRigidBody.h>

#include <hrengin/physics/IRayResultCallback.h>

namespace hrengin {
namespace awrts {

/* Enumeration for collision groups */
enum CollisionGroups : u16 {
	COL_NOTHING = 0,
	COL_DEFAULT = BIT(0),
	COL_STATIC = BIT(1),
	COL_GROUND = BIT(1),
	COL_UNIT = BIT(2),
	COL_SELECT = BIT(3),
	COL_DEBRIS = BIT(4),
	COL_EVERYTHING = static_cast<u16>(-1) //suppress warnings
};

class CExceptHimselfCallback : public physics::IClosestHitCallback {
public:
	static const bool singleHit = true;
	
	physics::ICollisionObject const* exclude_;
	
	CExceptHimselfCallback(physics::ICollisionObject const* exclude)
		: physics::IClosestHitCallback(), exclude_(exclude)
	{

	}
	
	virtual bool needsCollision(physics::BroadphaseProxy* proxy)
	{
		bool collides = physics::IClosestHitCallback::needsCollision(proxy);
		collides = collides && (proxy->clientObject != exclude_);
		return collides;
	}
};


} // namespace awrts
} // namespace hrengin

#endif//_awrts_Physics_
