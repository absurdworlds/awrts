#ifndef __H_INCLUDED__HRENGIN_IEntManager
#define __H_INCLUDED__HRENGIN_IEntManager

#include <hrengin/common/hrengintypes.h>
#include <hrengin/common/hrenginapi.h>

namespace hrengin
{

class IBaseEntity;

class IEntityManager
{
public:
	// run entity syncronization, snaps all entity components to new positions
	virtual void doSync() = 0;
	//virtual void doCleanup() = 0;

	virtual void addEntity(IBaseEntity* entity) = 0;
	virtual void deleteEntity(u32 entid) = 0;
};

HRENGIN_API IEntityManager& getEntityManager();
	
} // namespace hrengin

#endif//__H_INCLUDED__HRENGIN_IEntManager