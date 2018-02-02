/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_RigidBody_impl_
#define _aw_RigidBody_impl_
#include <stdio.h>

#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <aw/common/types.h>
#include <awrts/game/Entity.h>
#include <aw/physics/RigidBody.h>
//#include <aw/physics/PhysicsManager.h>

#include "CollisionObject.h"

namespace aw {
namespace physics {
namespace bullet {

//! Contains information needed to construct a rigid body
struct RigidBodyConstructionInfo {
public:
	//! Mass of the body
	//! If mass is zero, body is static
	f32 mass;

	// 
	CollisionFilter collisionFilterInfo;

	// NYI
	// const CollisionShape shape;

	f32 linearDamping;
	f32 angularDamping;

	// NYI
	// Vector3d<f32> localInertia;

	// 
	// MotionState* motionState;
	Vector3d<f32> position;
	//Vector4d<f32> rotation;

	f32 friction;
	f32 rollingFriction;
	f32 restitution;

	//! Default construction parameters
	RigidBodyConstructionInfo()
		: mass(1.0f),
		linearDamping(0.0f),
		angularDamping(0.0f),
		position(0.0f, 0.0f, 0.0f),
		friction(0.5f),
		rollingFriction(0.0f),
		restitution(0.0f)
	{
	}

	//! Construct specifying mass
	RigidBodyConstructionInfo(f32 mass)
		: mass(mass),
		linearDamping(0.0f),
		angularDamping(0.0f),
		position(0.0f, 0.0f, 0.0f),
		friction(0.5f),
		rollingFriction(0.0f),
		restitution(0.0f)
	{
	}
};


class RigidBody  {
public:
	RigidBody(btRigidBody* body);
	virtual ~RigidBody() = default;

	//! Set motion state \see MotionState
	virtual void setMotionState(MotionState* motionState);

	virtual void setPosition(Vector3d<f32> pos);
	virtual void setRotation(Vector3d<f32> rot);

	virtual Vector3d<f32> getPosition() const;
	virtual Vector3d<f32> getRotation() const;

	virtual CollisionObject::Details* getDetails()
	{
		return &details_;
	}
protected:
	CollisionObject::Details details_;
};

} // namespace bullet
} // namespace physics
} // namespace aw
#endif//_aw_RigidBody_impl_
