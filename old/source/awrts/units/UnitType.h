#ifndef _awrts_CUnitType_
#define _awrts_CUnitType_

#include <string>

#include <hrengin/common/types.h>

namespace hrengin {
namespace awrts {

struct UnitType {
	hrengin::u32 id;

	char * textUnitName;
	char * textDescription;
	
	char * visualModelName;

	hrengin::u32 guiSelectionShapeId;

	hrengin::f32 statsHitPointsMax;
	
	enum UnitMovementType {
		UM_STATIC = 0,
		UM_GROUND,
		UM_SWIMMING,
		UM_AMPHIBIOUS,
		UM_TRACKED,
		UM_WHEELED,
		UM_HOVER,
		UM_HOVER_AMPHIBIOUS,
		UM_AIRBORNE
	} movementType;
	hrengin::f32 movementHeight;
	hrengin::f32 movementSpeed;
	hrengin::f32 movementAcceleration;
	hrengin::f32 movementTurnSpeed;
	bool         movementCanReverse;
	hrengin::f32 movementReverseSpeed;
	hrengin::f32 movementReverseTurnSpeed;
	hrengin::f32 movementRequiredWidth;
	hrengin::f32 movementTurnRadius;
};

}
}

#endif//_awrts_CUnitType_