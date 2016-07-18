#ifndef _awrts_CGhostNavigator_
#define _awrts_CGhostNavigator_

/* mental note: make a nice 'load_defaults' function for videomgr */

#include <hrengin/ai/Path.h>
#include <hrengin/ai/IBaseNavigator.h>

namespace hrengin {
namespace ai {
class IBasePathfinder;
}

namespace awrts {

class CUnit;

using namespace hrengin::ai;

class CGhostNavigator : public IBaseNavigator {
public:
	CGhostNavigator(/*IBasePathfinder* pathfinder, */CUnit* unit);
	virtual ~CGhostNavigator();

	virtual void go (Vector3d<f32> target);
	virtual void follow (NavProxy* target);
	virtual void pursue (NavProxy* target);
	virtual void attach(IGroupNavigator* group) {};
	virtual void wander();
	virtual void abort();

	virtual void move(f32 step);

	virtual NavState getState() const;
protected:
	///* returns steering force towards target */
	//virtual Vector3d<f32> seek(Vector3d<f32> target);
	///* returns steering force away from target */
	//virtual Vector3d<f32> avoid(Vector3d<f32> target);
	virtual f32 getTurnAngle(Vector3d<f32> const& direction) const;
private:
	void prepareForMove(f32 step);
	void startMoving();
	void moveTo(f32 step);
	void arrive(f32 step);
	void align(f32 step);

	void steer(f32 angle, f32 step);
	void locomote(f32 step);


	CUnit* unit_;

	IBasePathfinder* pathfinder_;
	Path path_;
	size_t current_;

	IBaseNavigator::NavProxy* target_;
	IBaseNavigator::NavState state_;

	/*f32 const maxSpeed_;
	f32 const turnSpeed_;
	f32 const maxAcceleration_;
	f32 desiredSpeed_;*/

	enum InternalState {
		STATE_NORMAL,
		STATE_PRE,
		STATE_ALIGN,
		STATE_ARRIVE,
//		STATE_AVOID
	} status_;
};

} // namespace awrts
} // namespace hrengin

#endif//_awrts_CGhostNavigator_
