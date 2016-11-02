#ifndef __AWRTS_CNavigatorWheeled__
#define __AWRTS_CNavigatorWheeled__

#include <ai/CNavigatorGround.h>

namespace hrengin {
namespace ai {
class IBasePathfinder;
}

namespace awrts {

class CUnit;

using namespace hrengin::ai;

class CNavigatorWheeled : public CNavigatorGround {
public:
	CNavigatorWheeled(CUnit* unit, ILocomotor* locomotor, physics::IPhysicsWorld* world);
	virtual ~CNavigatorWheeled();

	//virtual void move(hrengin::f32 timeStep);
};

}
}

#endif//__AWRTS_CNavigatorWheeled__