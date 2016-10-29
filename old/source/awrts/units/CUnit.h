#ifndef _awrts_CUnit__
#define _awrts_CUnit__

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>
#include <hrengin/game/IBaseEntity.h>
#include <hrengin/game/IThinking.h>

#include "UnitType.h"

//#include "CUnitManager.h"

namespace hrengin {
class IEventManager;
namespace physics {
class ICollisionObject;
class IRigidBody;
}

namespace graphics {
class IVisNode;
}

namespace ai {
class IBaseNavigator;
}

namespace awrts {
class CUnitManager;
class ILocomotor;

enum OrderId {
	ORDER_NONE = 0,
	ORDER_MOVE = 'omov',
	ORDER_STAND = 'osta',
	ORDER_STOP = 'osto'
};

class CUnit : public IThinking {
public:
	~CUnit();

	CUnit(CUnitManager* umgr, UnitType& type,
		graphics::IVisNode* visual, 
		physics::ICollisionObject* selectionShape,
		IEventManager* eventmgr);

	u32 getUnitTypeID() const;

	virtual u32 getEntityIdentifier()
	{
		return 'unit';
	}

	virtual void onParentRemove() {};

	virtual void sync();
	virtual void think(hrengin::u32 time);

	void setNavigator(ai::IBaseNavigator* navigator);
	void setLocomotor(ILocomotor* locomotor);

	virtual Vector3d<f32> getPosition() const;
	virtual Vector3d<f32> getRotation() const;
	virtual f32 getFacing() const;

	virtual void setPosition(Vector3d<f32>position);
	virtual void setRotation(Vector3d<f32>rotation);
	virtual void setFacing(float angle);
	virtual void enterDeleteQueue() {};

	virtual bool issuePointOrder(OrderId order, Vector3d<f32>pos);
	virtual bool issueImmediateOrder(OrderId order);

	virtual physics::ICollisionObject const* getPhysicsShape() const
	{
		return selectionShape_;
	}
protected:
	virtual void move(float timeStep);

private:
	hrengin::u32 typeId;

	graphics::IVisNode*	visual_;
	//hrengin::physics::IPhysicsPhantom*	selectionShape_;
	physics::ICollisionObject*	selectionShape_;

	Vector3d<f32> position_;
	Vector3d<f32> rotation_;

	hrengin::u32 lastThink_;

	// todo: give this class a name
	struct {
		OrderId orderId;
		union {
			hrengin::u32 targetId;
			struct {
				hrengin::f32 targetX;
				hrengin::f32 targetY;
			};
		};
	} order_;

	hrengin::u32 eventId_;

	ai::IBaseNavigator* navigator_;
	ILocomotor* locomotor_;
};

void getStringFromUnitId(hrengin::u32 unitId, unsigned char* output);

}
} //namespace hrengin


#endif//__H_INCLUDED__AWRTS_CUnit