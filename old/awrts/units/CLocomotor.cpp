
#include <hrengin/common/math.h>

#include <units/CLocomotor.h>

namespace hrengin {
namespace awrts {

CLocomotor::CLocomotor(CUnit* owner, UnitType const& type)
	: ILocomotor(owner, type), angular_(0)
{
	owner->setLocomotor(this);
}

void CLocomotor::locomote(f32 timeDelta)
{
	Vector3d<f32> pos = unit_->getPosition();
	Vector3d<f32> rot = unit_->getRotation();

	rot.y += angular_*timeDelta;

	unit_->setRotation(rot);

	printf("%f %f\n", acceleration_.length(),desiredSpeed_);

	updateVelocity();

	unit_->setPosition(pos + velocity_*timeDelta);
}

void CLocomotor::updateVelocity()
{
	f32 facing = math::DegToRad(unit_->getFacing());
	f32 speed = velocity_.length();
	f32 acceleration = 0.0f;

	if(!math::equals(speed, desiredSpeed_)) {
		acceleration = math::clamp(desiredSpeed_ - speed,
			-maxAcceleration_, maxAcceleration_);
		speed = math::clamp(speed + acceleration,
			-maxSpeed_, maxSpeed_);

		acceleration_ = Vector3d<f32>(sin(facing)*acceleration, 0,
			cos(facing)*acceleration);
	} else {
		acceleration_.set(0,0,0);
	}

	velocity_ = Vector3d<f32>(sin(facing)*speed, 0, cos(facing)*speed);
}

void CLocomotor::move(Vector3d<f32> force)
{
}

void CLocomotor::steer(Vector3d<f32> force)
{
}

void CLocomotor::rotate(f32 dps)
{
	angular_ = math::clamp(dps, -maxTurnSpeed_, maxTurnSpeed_);
}

void CLocomotor::accelerate(f32 factor)
{
	desiredSpeed_ = maxSpeed_ * factor;
}

void CLocomotor::brake(f32 factor)
{
	desiredSpeed_ = maxSpeed_ * (1 - factor);
}


} // namespace awrts
} // namespace hrengin
