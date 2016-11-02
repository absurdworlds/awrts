#ifndef _awrts_CPlayerCommander_
#define _awrts_CPlayerCommander_

#include <vector>

#include <hrengin/common/line3d.h>

#include "ICommander.h"

namespace hrengin {
namespace awrts {

class CPlayerCommander : public ICommander {
public:
	virtual CUnitGroup* selectUnitGroup(u32 groupId);
	virtual void removeUnitGroup(u32 groupId);
	virtual void addUnitToGroup(u32 groupId);

	virtual u32 storeSelection();
	
	virtual void deselect();
	virtual void selectUnitsInRect();
	virtual void selectUnit(hrengin::base::line3df ray);

	virtual void issueTargetOrder();
	virtual void issuePointOrder();
	virtual void issueImmediateOrder();
private:
	std::vector<CUnitGroup> groups_;
};

}
}

#endif//_awrts_CPlayerCommander_
