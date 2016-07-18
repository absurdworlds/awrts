#ifndef _awrts_CNavigatorGround_
#define _awrts_CNavigatorGround_

#include <hrengin/ai/Path.h>
#include <hrengin/ai/IBaseNavigator.h>
#include <hrengin/physics/IPhysicsWorld.h>

namespace hrengin {
namespace ai {
class IBasePathfinder;
}

namespace awrts {

class CUnit;
class ILocomotor;

using namespace hrengin::ai;

class CNavigatorGround : public IBaseNavigator {
public:
	CNavigatorGround(CUnit* unit, ILocomotor* locomotor, physics::IPhysicsWorld* world);
	virtual ~CNavigatorGround();
	//virtual void SetPathfinder(IBasePathfinder* pathfinder) = 0;
		
	//
	virtual bool checkState(NavState state);
	virtual NavState getState() const;

	virtual void go(Vector3d<f32> destination);
	virtual void follow (NavProxy* target) {};
	virtual void pursue (NavProxy* target) {};
	virtual void attach(IGroupNavigator* group) {};
	virtual void wander() {};
	virtual void abort();

	virtual void navigate(f32 timeDelta);

protected:
	virtual void movePrepare(f32 timeDelta);
	virtual void moveTo(f32 timeDelta);

	virtual Vector3d<f32> calculateAvoidanceVector(Vector3d<f32> const& direction);

	physics::IPhysicsWorld* world_;

	i32 current_;
	Path path_;

	CUnit* unit_;
	ILocomotor* locomotor_;

	IBasePathfinder* pathfinder_;
	
	NavState navState_;
	enum InternalState {
		STATE_NORMAL,
		STATE_PREMOVE,
		STATE_ALIGN,
		STATE_ARRIVE,
//		STATE_AVOID
	} status_;
};

}
}

#endif//__AWRTS_CNavigatorGround__
