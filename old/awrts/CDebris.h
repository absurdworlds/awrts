#ifndef _awrts_CDebris_
#define _awrts_CDebris_

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/game/IBaseEntity.h>
#include <hrengin/game/IThinking.h>

#include <hrengin/scene/IVisNode.h>
#include <hrengin/scene/ISceneManager.h>
#include <hrengin/physics/IPhysicsManager.h>
#include <hrengin/physics/IRigidBody.h>

namespace hrengin {
namespace awrts {

class CDebris : public hrengin::IEntity {
	public:
		CDebris(Vector3d<f32> pos, physics::IPhysicsManager* phymgr, physics::IPhysicsWorld* world,
			 graphics::ISceneManager* scnmgr, IEntityManager* entmgr)
		{
			pos.y += 20.0;
			
			physics::IRigidBody::RigidBodyConstructionInfo rbInfo;

			rbInfo.mass = 5.0f;
			rbInfo.position = pos;
			rbInfo.friction = 1.0f;
			rbInfo.rollingFriction = 0.3f;

			physics_ = phymgr->createBody("oildrum.hdf", rbInfo);
			physics::CollisionFilter colFilter(COL_DEBRIS, COL_GROUND | COL_DEBRIS | COL_UNIT);

			world->addBody(physics_);
			//visual_ = scnmgr->createMeshSceneNode("crate10x10.3DS");
			

			entmgr->addEntity(this);

			sync();
		}

		~CDebris()
		{
			
		}

		virtual hrengin::u32 getEntityIdentifier()
		{
			return 'dbri';
		}

		virtual void onParentRemove()
		{
		};

		virtual void sync()
		{
			Vector3d<f32>position__ = physics_->getPosition();
			Vector3d<f32>rotation__ = physics_->getRotation();

			//visual_->setPosition(position__);
			//visual_->setRotation(rotation__);
		};


		virtual void setPosition(Vector3d<f32>position)
		{
		
		}

		virtual void setRotation(Vector3d<f32>rotation)
		{
		
		}

		virtual Vector3d<f32> getPosition() const
		{
			return physics_->getPosition();
		}

		virtual Vector3d<f32> getRotation() const
		{
			return physics_->getRotation();
		}

		virtual void enterDeleteQueue() {};

	private:
		graphics::IVisNode*	visual_;
		physics::IRigidBody*	physics_;
};

} // namespace awrts
} // namespace hrengin


#endif//__AWRTS_CDebris__
