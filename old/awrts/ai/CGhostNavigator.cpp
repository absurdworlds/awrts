
#include <hrengin/common/math.h>
#include <hrengin/common/Line3d.h>
#include <hrengin/ai/IBasePathfinder.h>
#include <hrengin/ai/NavigatorUtils.h>
#include <hrengin/game/IBaseEntity.h>

#include <ai/CGhostNavigator.h>
#include <units/CUnit.h>

namespace hrengin {
namespace awrts {

CGhostNavigator::CGhostNavigator(/*IBasePathfinder* pathfinder, */CUnit* unit)
	: /*pathfinder_(pathfinder),*/ current_(0), unit_(unit)
{
	//proxy_.client = unit;
	unit_->setNavigator(this);
	pathfinder_ = createSimplePathfinder();
}

CGhostNavigator::~CGhostNavigator()
{

}

CGhostNavigator::NavState CGhostNavigator::getState() const
{
	return state_;
}


void CGhostNavigator::go (Vector3d<f32> target)
{
	path_ = pathfinder_->findPath(unit_->getPosition(), target);
	current_ = 0;
	state_= NavState::MoveTo;
	status_ = STATE_PRE;
}

void CGhostNavigator::follow (NavProxy* target)
{
	target_ = target;
	state_ = NavState::Follow;
	status_ = STATE_PRE;
}

void CGhostNavigator::pursue (NavProxy* target)
{
	target_ = target;
	state_ = NavState::Pursue;
	status_ = STATE_PRE;
}

void CGhostNavigator::wander()
{

}

void CGhostNavigator::abort()
{
	state_ = NavState::Idle;
}

void CGhostNavigator::move(f32 step)
{
	switch(state_) {
	default:
	case NavState::Idle:
		break;
	case NavState::MoveTo:
		switch(status_) {
		case STATE_PRE:
			prepareForMove(step);
			break;
		case STATE_ALIGN:
			align(step);
			break;
		case STATE_ARRIVE:
			arrive(step);
			break;
		case STATE_NORMAL:
		default:
			moveTo(step);
			break;
		}
		break;
	}
}

void CGhostNavigator::prepareForMove(f32 step)
{
	if(path_.size() < 2) {
		state_ = NavState::Idle;
		return;
	}

	Vector3d<f32> direction = path_[current_] - unit_->getPosition();

	f32 turnAngle = getTurnAngle(direction);
	

	if(turnAngle > 60) {
		status_ = STATE_ALIGN;
	} else {
		startMoving();
	}
}

void CGhostNavigator::startMoving()
{
	if(path_.size() - current_ > 2) {
		status_ = STATE_NORMAL;
	} else {
		status_ = STATE_ARRIVE;
	}
}

void CGhostNavigator::moveTo(f32 step)
{
#if 0
	f32 const moveSpeed = unit_->getMoveSpeed();
	
	Vector3d<f32> direction = path_[current_] - unit_->getPosition();

	if(direction.length() < 5.0) {
		if(current_ == path_.size() - 2) {
			status_ = STATE_ARRIVE;
		}
		current_++;
	}
	
	f32 turnAngle = getTurnAngle(direction);

	steer(turnAngle, step);
	locomote(step);
#endif
}

void CGhostNavigator::align(f32 step)
{
#if 0
	Vector3d<f32> direction = path_[current_] - unit_->getPosition();

	f32 const turnAngle = getTurnAngle(direction);
	f32 const turnStep = unit_->getTurnSpeed()*step;

	hrengin::f32 turnDir = turnAngle > 0.0f ? 1.0f : -1.0f;

	if(abs(turnAngle) > turnStep) {
		steer(turnAngle, step);
	} else {
		startMoving();
	}
#endif
}

void CGhostNavigator::arrive(f32 step)
{
#if 0
	f32 moveSpeed = unit_->getMoveSpeed();
	
	Vector3d<f32> direction = path_.last() - unit_->getPosition();

	if(direction.length() < moveSpeed*step) {
		unit_->setPosition(path_.last());
		status_ = STATE_PRE;
		state_ = NavState::Idle;
		current_++;
		return;
	}
	
	f32 turnAngle = getTurnAngle(direction);

	steer(turnAngle, step);
	locomote(step);
#endif
}

f32 CGhostNavigator::getTurnAngle(Vector3d<f32> const& direction) const
{
	f32 unitFacing = unit_->getFacing();
	f32 targetAngle = math::wrapAngle(direction.getYaw());
	f32 turnAngle = math::normalizeAngle(targetAngle - unitFacing);

	return turnAngle;
}


void CGhostNavigator::steer(f32 angle, f32 step)
{
#if 0
	f32 const unitFacing = unit_->getFacing();
	f32 const turnStep = unit_->getTurnSpeed()*step;

	hrengin::f32 turnDir = angle > 0.0f ? 1.0f : -1.0f;
	

	if(abs(angle) > turnStep) {
		unit_->setFacing(unitFacing + turnDir * turnStep);
	} else {
		unit_->setFacing(unitFacing + angle);
	}
#endif
}

void CGhostNavigator::locomote(f32 step)
{
#if 0
	f32 const unitFacing = unit_->getFacing();
	f32 const moveSpeed = unit_->getMoveSpeed();

	Vector3d<f32> velocity;

	velocity.X = sin(unitFacing * hrengin::math::DEGTORAD);
	velocity.Z = cos(unitFacing * hrengin::math::DEGTORAD);
	velocity *= moveSpeed;
	
	unit_->setPosition(unit_->getPosition() + velocity * step);
#endif
}

} // namespace awrts
} // namespace hrengin
