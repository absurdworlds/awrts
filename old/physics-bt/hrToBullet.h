/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_hrToBullet_
#define _aw_hrToBullet_
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <aw/math/Vector3d.h>

namespace aw {
namespace physics {

inline Vector3d<f32> toHrengin(btVector3 const& btVec)
{
	return Vector3d<f32>(btVec[0], btVec[1], btVec[2]);
}

inline btVector3 toBullet(Vector3d<f32> const& hrVec)
{
	return btVector3(hrVec[0], hrVec[1], hrVec[2]);
}

// TODO: replace this with toHrengin() and toBullet() quaternion converion, to remove duplicate code
void quaternionToEuler(btQuaternion const& quat, btVector3& euler);

} // namespace physics
} // namespace aw
#endif //_aw_hrToBullet_
