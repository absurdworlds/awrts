/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_BulletPhysics_impl_
#define _aw_BulletPhysics_impl_
#include <map>
#include <string>
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/btBulletCollisionCommon.h>

#include <aw/physics/PhysicsManager.h>

namespace aw {
struct Primitive;
struct SMesh;

class Model;

namespace physics {
class CollisionPhantom;
class RigidBody;

class BulletPhysics : public PhysicsManager {
public:
	BulletPhysics();
	virtual ~BulletPhysics();

	virtual u32 loadModel(char const* modelName);

	virtual RigidBody* createBody(u32 const modelId, RigidBody::RigidBodyConstructionInfo cInfo);
	virtual RigidBody* createBody(char const* modelName, RigidBody::RigidBodyConstructionInfo cInfo);

	virtual CollisionPhantom* createPhantom(u32 const modelId);
	virtual CollisionPhantom* createPhantom(char const* modelName);

	virtual PhysicsWorld* createPhysicsWorld();

	virtual DebugDrawer* createDebugDrawer(graphics::RenderingDevice* renderer);

private:
	virtual u32 addShape(Model* model);
	virtual btCollisionShape* createPrimitiveShape(Primitive shape);
	//virtual btCollisionShape* createMeshShape(SMesh shape);

	core::ModelLoader* modelLoader_;

	std::map<std::string,u32> models_;
	btAlignedObjectArray<btCollisionShape*> collisionShapes_;
};

} // namespace physics
} // namespace aw
#endif//_aw_BulletPhysics_impl_
