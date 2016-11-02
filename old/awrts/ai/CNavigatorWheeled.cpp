
#include <hrengin/common/math.h>
#include <hrengin/ai/IBasePathfinder.h>

#include "../units/CUnit.h"

#include "CNavigatorWheeled.h"

namespace hrengin {
namespace awrts {

CNavigatorWheeled::CNavigatorWheeled(CUnit* unit, ILocomotor* locomotor, physics::IPhysicsWorld* world)
	: CNavigatorGround(unit, locomotor, world)
{

}

CNavigatorWheeled::~CNavigatorWheeled()
{
	delete pathfinder_;
}
#if 0
void CNavigatorWheeled::move(hrengin::f32 timeStep)
{
	using hrengin::math::wrapAngle;

	if(!moving_) {
		return;
	}

	hrengin::f32 moveSpeed = unit_.getMoveSpeed();

	Vector3d<f32> destination = path_[current_];
	Vector3d<f32> direction = destination - unit_.getPosition();

	if(direction.length() < 1.01*moveSpeed * timeStep) {
		if(current_ == path_.size()-1) {
			abort();
			return;
		} else {
			current_ ++;
			moveFinished_ = true;
			move(timeStep);
			return;
		}
	}

	hrengin::f32 turnSpeed = unit_.getTurnSpeed();

	hrengin::f32 targetAngle = wrapAngle(direction.getYaw());
	hrengin::f32 unitFacing = unit_.getFacing();
	hrengin::f32 turnAngle = wrapAngle(targetAngle - unitFacing);
	
	static int kostul = 0;
	static int kostul2 = 0;

	if(moveFinished_) {
		hrengin::f32 turnRadius = moveSpeed/(turnSpeed * hrengin::math::DEGTORAD);
		checkArc(turnRadius, turnAngle, direction.length());
		if(alignFirst_) kostul = -8;
		moveFinished_ = false;
	}

	bool aligned = rotate(turnSpeed * timeStep, targetAngle);

	Vector3d<f32>velocity;

	//printf("a");

	if(alignFirst_ && (!aligned || kostul < 0)) {
		velocity.X = sin(unitFacing * hrengin::math::DEGTORAD);
		velocity.Z = cos(unitFacing * hrengin::math::DEGTORAD);
		velocity *= - (moveSpeed * 0.5);

		kostul += 1;
		kostul2 = 4;

		rotate(-.20 * turnSpeed * timeStep, targetAngle);
	} else {
		if(kostul2) {
			kostul2 -= 1;
			return;
		
		}
		alignFirst_ = false;

		velocity.X = sin(unitFacing * hrengin::math::DEGTORAD);
		velocity.Z = cos(unitFacing * hrengin::math::DEGTORAD);
		velocity *= moveSpeed;

		kostul = 0;
	}

	unit_.setPosition(unit_.getPosition() + velocity * timeStep);
}
#endif

}
}
