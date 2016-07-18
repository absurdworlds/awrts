
#include <hrengin/common/math.h>
#include <hrengin/platform/time.h>
#include <hrengin/scene/IVisNode.h>
#include <hrengin/ai/IBaseNavigator.h>
#include <hrengin/game/IEventManager.h>

#include <Physics.h>

#include <units/ILocomotor.h>

#include "CUnit.h"

namespace hrengin {
namespace awrts {

CUnit::CUnit(CUnitManager* umgr, UnitType& type,
		graphics::IVisNode* visual, 
		physics::ICollisionObject* selectionShape,
		IEventManager* eventmgr)
	: typeId(type.id), visual_(visual), selectionShape_(selectionShape),
	locomotor_(nullptr), navigator_(nullptr)
{
	hrengin::Event thinkEvent;

	thinkEvent.owner = this;
	thinkEvent.isActive = true;
	thinkEvent.nextFire = hrengin::getTime() + 30;
	thinkEvent.period = 20;

	lastThink_ = hrengin::getTime();
	eventId_ = eventmgr->addEvent(thinkEvent);
}

CUnit::~CUnit()
{
	if(navigator_) {
		delete navigator_;
	}
	if(locomotor_) {
		delete locomotor_;
	}
}

void CUnit::setNavigator(hrengin::ai::IBaseNavigator* navigator)
{
	if(navigator_) {
		delete navigator_;
	}
	navigator_ = navigator;
}

void CUnit::setLocomotor(ILocomotor* locomotor)
{
	if(locomotor_) {
		delete locomotor_;
	}
	locomotor_ = locomotor; 
}

void CUnit::setPosition(Vector3d<f32> position)
{
	selectionShape_->setPosition(position);
}

void CUnit::setRotation(Vector3d<f32> rotation)
{
	selectionShape_->setRotation(rotation);
}

Vector3d<f32>CUnit::getPosition() const
{
	return selectionShape_->getPosition();
}


Vector3d<f32>CUnit::getRotation() const
{
	return selectionShape_->getRotation();
}

void CUnit::setFacing(f32 angle)
{
	angle = math::wrapAngle(angle);

	Vector3d<f32> rotation = getRotation();
	rotation.y = angle;
	selectionShape_->setRotation(rotation);
}

float CUnit::getFacing() const
{
	return selectionShape_->getRotation().y;
}

void CUnit::sync()
{
	Vector3d<f32> position = selectionShape_->getPosition();
	Vector3d<f32> rotation = selectionShape_->getRotation();

	visual_->setPosition(position);
	visual_->setRotation(rotation);
}

void CUnit::move(float timeStep)
{
	navigator_->navigate(timeStep); // Capt. Obvious
	locomotor_->locomote(timeStep);
	
	if(navigator_->getState() == ai::IBaseNavigator::NavState::Idle) {
		order_.orderId = ORDER_STOP;
	}
}

void CUnit::think(hrengin::u32 time)
{
	hrengin::f32 timeStep = (time - lastThink_) / 1000.0f;
	
	lastThink_ = time;

	//reminder: rewrite it to setNextThink 

	switch(order_.orderId) {
	case ORDER_MOVE: {
		move(timeStep);

		break;
	}
	default:
		break;
	}
}

hrengin::u32 CUnit::getUnitTypeID() const
{
	return typeId;
}

bool CUnit::issueImmediateOrder(OrderId order)
{
	switch(order) {
	case ORDER_STOP:
		navigator_->abort();
		break;
	default:
		return false;
	}

	order_.orderId = order;
	return true;
}

bool CUnit::issuePointOrder(OrderId order, Vector3d<f32>pos)
{
	switch(order) {
	case ORDER_MOVE:
		navigator_->go(pos);
		break;
	default:
		return false;
	}

	order_.orderId = order;
	order_.targetX = pos.x;
	order_.targetY = pos.y;
	return true;
}


void getStringFromUnitId(hrengin::u32 unitId, unsigned char* output)
{
	output[0] = (unitId >> 24) & 0xFF;
	output[1] = (unitId >> 16) & 0xFF;
	output[2] = (unitId >> 8)  & 0xFF;
	output[3] = (unitId >> 0)  & 0xFF;
	output[4] = 0;
}

} // namespace awrts
} // namespace hrengin
