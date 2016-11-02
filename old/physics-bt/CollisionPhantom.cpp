/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include "CollisionPhantom.h"
#include "hrToBullet.h"

namespace aw {
namespace physics {
namespace bullet {

CollisionPhantom::CollisionPhantom(btCollisionObject* object)
	: details_(object)
{
	details_.obj->setUserPointer(this);
}

void CollisionPhantom::setPosition(Vector3d<f32> pos)
{
	btTransform transform = details_.obj->getWorldTransform();
	transform.setOrigin(toBullet(pos));
#if 0
	btVector3 origin(pos.X,pos.Y,pos.Z);
	localTransform.setIdentity();
	localTransform.setRotation(details_.obj->getWorldTransform().getRotation());
#endif

	details_.obj->setWorldTransform(transform);
};

void CollisionPhantom::setRotation(Vector3d<f32> rot)
{
	btTransform transform = details_.obj->getWorldTransform();
#if 0
	localTransform.setIdentity();
	localTransform.setOrigin(details_.obj->getWorldTransform().getOrigin());
#endif
	rot *= math::RadiansInDegree;
	transform.setRotation(btQuaternion(rot[1], rot[0], rot[2]));
	details_.obj->setWorldTransform(transform);
};

Vector3d<f32> CollisionPhantom::getPosition() const
{
	btVector3 pos = details_.obj->getWorldTransform().getOrigin();

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};

Vector3d<f32> CollisionPhantom::getRotation() const
{
	btQuaternion rot = details_.obj->getWorldTransform().getRotation();

	btVector3 pos;
	quaternionToEuler(rot,pos);

	return Vector3d<f32>(pos.getX(),pos.getY(),pos.getZ());
};
} // namespace bullet
} // namespace physics
} // namespace aw
