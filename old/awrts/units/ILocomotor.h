#ifndef _awrts_ILocomotor_
#define _awrts_ILocomotor_

#include <hrengin/common/Vector3d.h>

#include <units/CUnit.h>

namespace hrengin {
namespace awrts {

class ILocomotor {
public:
	// todo: replace with locomotorType & UnitType overrides
	ILocomotor(CUnit* owner, UnitType const& type)
		: unit_(owner)
	{
		maxSpeed_ = type.movementSpeed;
		maxAcceleration_ = type.movementAcceleration;
		maxTurnSpeed_ = type.movementTurnSpeed;
	}

	virtual ~ILocomotor()
	{
	}

	virtual void locomote(f32 timeDelta) = 0;

	virtual void move(Vector3d<f32> force) = 0;

	/** Apply steering force
	   @note
	   How steering force is processed depends on implementation of
	   locomotor
	   @param force
	   Steering force to apply
	 */
	virtual void steer(Vector3d<f32> force) = 0;
	
	/** Apply angular velocity
	   @param dps
	   Angular velocity in degrees per second
	 */
	virtual void rotate(f32 dps) = 0;
	
	/** Accelerate to a 
	   @param factor
	   Angular velocity in degrees per second
	 */
	virtual void accelerate(f32 factor) = 0;
	virtual void brake(f32 factor) = 0;

	virtual Vector3d<f32> getVelocity() const = 0;

	virtual Vector3d<f32> getAcceleration() const = 0;

	virtual f32 getAngularVelocity() const = 0;

	virtual f32 getMaxSpeed() const
	{
		return maxSpeed_;
	}
	virtual f32 getMaxAcceleration() const
	{
		return maxAcceleration_;
	}
	virtual f32 getTurnSpeed() const
	{
		return maxTurnSpeed_;
	}

protected:
	CUnit* unit_;

	f32 maxSpeed_;
	f32 maxAcceleration_;
	f32 maxTurnSpeed_;
};

} // namespace awrts
} // namespace hrengin

#endif//_awrts_ILocomotor_
