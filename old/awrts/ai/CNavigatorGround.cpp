
#include <hrengin/common/math.h>
#include <hrengin/common/Line3d.h>

#include <hrengin/ai/IBasePathfinder.h>

#include <units/CUnit.h>
#include <units/ILocomotor.h>

#include <Physics.h>
#include <awrts.h>
#include <CGame.h>

#include "CNavigatorGround.h"

namespace hrengin {
namespace awrts {

CNavigatorGround::CNavigatorGround(CUnit* unit, ILocomotor* locomotor,
	physics::IPhysicsWorld* world)
	: unit_(unit), locomotor_(locomotor), current_(0), world_(world),
	  navState_(IBaseNavigator::NavState::Idle), status_(STATE_PREMOVE)
{
	unit_->setNavigator(this);
	pathfinder_ = createSimplePathfinder();
}

CNavigatorGround::~CNavigatorGround()
{
	delete pathfinder_;
}


bool CNavigatorGround::checkState(NavState state)
{
	return false;
}

IBaseNavigator::NavState CNavigatorGround::getState() const
{
	return navState_;
}

void CNavigatorGround::go(Vector3d<f32> destination)
{
	path_ = pathfinder_->findPath(unit_->getPosition(), destination);

	navState_ = NavState::MoveTo;
	status_ = STATE_PREMOVE;
}

void CNavigatorGround::navigate(f32 timeDelta)
{
	switch(navState_) {
	case NavState::MoveTo:
		switch (status_) {
		case STATE_ALIGN:
		case STATE_ARRIVE:
		case STATE_NORMAL:
			moveTo(timeDelta);
			break;
		case STATE_PREMOVE:
			movePrepare(timeDelta);
			break;
			break;
			break;
		default:
			break;
		}
	default:
	case NavState::Idle:
		break;
	}
}


void CNavigatorGround::movePrepare(f32 timeDelta)
{
	f32 moveSpeed = locomotor_->getMaxSpeed();
	f32 turnSpeed = locomotor_->getTurnSpeed();

	Vector3d<f32> destination = path_[current_];
	destination.y = unit_->getPosition().y;
	Vector3d<f32> direction = destination - unit_->getPosition();
	
	hrengin::f32 targetAngle = math::wrapAngle(direction.getYaw());
	hrengin::f32 unitFacing = unit_->getFacing();
	hrengin::f32 turnAngle = math::wrapAngle(targetAngle - unitFacing);

	hrengin::f32 turnRadius = moveSpeed/math::DegToRad(turnSpeed);
	hrengin::f32 turnArc = abs(math::DegToRad(turnRadius*turnAngle));

	if(direction.length() < 5*turnArc) {
		status_ = STATE_ALIGN;
	} else {
		status_ = STATE_NORMAL;
	}
}

void CNavigatorGround::moveTo(f32 timeDelta)
{
	static f32 const threshold = 1.0f;
	f32 moveSpeed = locomotor_->getMaxSpeed();

	Vector3d<f32> destination = path_[current_];
	destination.y = unit_->getPosition().y;
	Vector3d<f32> direction = destination - unit_->getPosition();

	if(direction.length() <= moveSpeed * timeDelta) {
		if(current_ == path_.size()-1) {
			//unit_->setPosition(path_[current_]);
			abort();
			return;
		} else {
			current_ ++;
			status_ = STATE_PREMOVE;
			moveTo(timeDelta);
			return;
		}
	}
	f32 turnSpeed = locomotor_->getTurnSpeed();
	
	if(locomotor_->getVelocity().length() > 0) {
		direction = calculateAvoidanceVector(direction);
	}

	f32 targetAngle = math::wrapAngle(direction.getYaw());
	f32 unitFacing = unit_->getFacing();
	f32 turnAngle = math::wrapAngle(targetAngle - unitFacing);
	

	if(abs(turnAngle) > timeDelta*turnSpeed) {
		hrengin::f32 turnDir = turnAngle > 0.0f ? 1.0f : -1.0f;
		locomotor_->rotate(turnSpeed*turnDir);
	} else {
		locomotor_->rotate(turnAngle);
	}
	
	if(status_ == STATE_ALIGN) {
		if(turnAngle < timeDelta*turnSpeed) {
			status_ = STATE_NORMAL;
		} else {
			locomotor_->brake(1.0f);
			return;
		}
	}

	

/*	
	if(callback.hasHit() || callback2.hasHit() || callback3.hasHit()) {
		locomotor_->brake(1.0f);
		return;
	}*/
	
	locomotor_->accelerate(1.0f);
}

void CNavigatorGround::abort()
{
	navState_ = NavState::Idle;
}

Vector3d<f32> CNavigatorGround::calculateAvoidanceVector(Vector3d<f32> const& direction)
{
	graphics::IRenderingDevice* rundurur = getGameManager().getRenderer();

	CExceptHimselfCallback callback(unit_->getPhysicsShape());
	callback.collFilter = physics::CollisionFilter(COL_UNIT,COL_UNIT);

	Vector3d<f32> position = unit_->getPosition();
	Vector3d<f32> velocity = locomotor_->getVelocity();

	Line3d<f32> ray(position, position + 1.5*velocity);
	
	world_->castRay(ray.start, ray.end, &callback);
	rundurur->drawLine(ray.start+Vector3d<f32>(0,0.5,0),
		ray.end+Vector3d<f32>(0,0.5,0),
		Vector3d<f32>(0,255,0));

	if(!callback.hasHit()) {
		return direction;
	}

	if((callback.hitPoint - position).length() > direction.length()) {
		return direction;
	}

	callback.collObject = 0;

	f32 const facing = math::DegToRad(90.0f + unit_->getFacing());
	Vector3d<f32> heading(sin(facing),0,cos(facing));

	ray.end = position + 1.5*velocity + 3*heading;
	world_->castRay(ray.start, ray.end, &callback);
	rundurur->drawLine(ray.start+Vector3d<f32>(0,0.5,0),
		ray.end+Vector3d<f32>(0,0.5,0),
		Vector3d<f32>(0,0,255));

	if(!callback.hasHit()) {
		// move in this direction
		return ray.vector();
	}
		
	ray.end = position + 1.5*velocity - 3*heading;
	world_->castRay(ray.start, ray.end, &callback);
	rundurur->drawLine(ray.start+Vector3d<f32>(0,0.5,0),
		ray.end+Vector3d<f32>(0,0.5,0),
		Vector3d<f32>(255,0,0));
		
	if(!callback.hasHit()) {
		// move in this direction
		return ray.vector();
	} else {
		// panic
		return Vector3d<f32>::zero;
	}
	
	return direction;
}

} // namespace awrts
} // namespace hrengin
