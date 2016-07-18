#ifndef _awrts_CLocomotor_
#define _awrts_CLocomotor_

#include <hrengin/common/Vector3d.h>

#include <units/CUnit.h>
#include <units/ILocomotor.h>

namespace hrengin {
namespace awrts {

class CLocomotor : public ILocomotor {
public:
	CLocomotor(CUnit* owner, UnitType const& type);
	virtual ~CLocomotor()
	{
	}

	virtual void locomote(f32 timeDelta);

	virtual void move(Vector3d<f32> force);

	virtual void steer(Vector3d<f32> force);

	virtual void rotate(f32 dps);

	virtual void accelerate(f32 factor);
	virtual void brake(f32 factor);
	
	virtual Vector3d<f32> getVelocity() const
	{
		return velocity_;
	}

	virtual Vector3d<f32> getAcceleration() const
	{
		return acceleration_;
	}

	virtual f32 getAngularVelocity() const
	{
		return angular_;
	}
private:
	void updateVelocity();

	f32 desiredSpeed_;

	Vector3d<f32> velocity_;
	Vector3d<f32> acceleration_;
	f32 angular_;
};

} // namespace awrts
} // namespace hrengin

#endif//_awrts_CLocomotor_
