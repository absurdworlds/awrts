#ifndef _awrts_ICommander_
#define _awrts_ICommander_

#include <hrengin/common/types.h>
#include <hrengin/common/Vector3d.h>

#include "../Units/CUnitGroup.h"

namespace hrengin {
namespace awrts {

class ICommander {
public:
	virtual CUnitGroup* selectUnitGroup(u32 groupId) = 0;
	virtual void removeUnitGroup(u32 groupId) = 0;
	virtual void addUnitToGroup(u32 groupId) = 0;

	virtual u32 storeSelection() = 0;
	
	virtual void deselect() = 0;

	virtual void issueTargetOrder() = 0;
	virtual void issuePointOrder() = 0;
	virtual void issueImmediateOrder() = 0;
};

}
}

#endif//_awrts_ICommander_
