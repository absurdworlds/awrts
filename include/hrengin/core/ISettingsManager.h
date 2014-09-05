#ifndef _hrengin_ISettingsManager_
#define _hrengin_ISettingsManager_

#include <string>

#include <hrengin/common/api.h>
#include <hrengin/common/types.h>
#include <hrengin/core/hdf.h>

namespace hrengin {
namespace core {

class ISettingsManager {
public:
	virtual ~ISettingsManager() {};

	virtual void loadSettings() = 0;

	//virtual void registerSetting(std::string key, hdf::Type type) = 0;

	virtual bool getValue(std::string key, std::string& val) = 0;
	virtual bool getValue(std::string key, f64& val) = 0;
	virtual bool getValue(std::string key, i32& val) = 0;
	virtual bool getValue(std::string key, bool& val) = 0;

	virtual bool setValue(std::string key, std::string val) = 0;
	virtual bool setValue(std::string key, f64 val) = 0;
	virtual bool setValue(std::string key, i32 val) = 0;
	virtual bool setValue(std::string key, bool val) = 0;
};

HR_CORE_API ISettingsManager& getSettingsManager();
//HR_CORE_API ISettingsManager* createSettingsManager();

} // namespace core
} // namespace hrengin


#endif//_hrengin_ISettingsManager_
