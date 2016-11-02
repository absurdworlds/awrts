/*
 * Copyright (C) 2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_irr_logger_h
#define aw_internal_irr_logger_h
#include <Irrlicht/os.h>
#include <awrts/logging.h>
namespace aw::graphics {

struct logger : irr::ILogger {
	void log(const irr::c8* text, irr::ELOG_LEVEL ll) override
	{
		using namespace irr;
		aw::log::level lvl = [ll] {
			switch (ll) {
			case ELL_DEBUG:       return aw::log::level::info;
			case ELL_INFORMATION: return aw::log::level::info;
			case ELL_WARNING:     return aw::log::level::warning;
			case ELL_ERROR:       return aw::log::level::error;
			case ELL_NONE:        return aw::log::level::info;
			}
		}();

		journal.message(lvl, "Irrlicht", text);
	}

	void log(const irr::c8* text, const irr::c8* hint, irr::ELOG_LEVEL ll) override
	{
		log(text,ll);
		log(hint,ll);
	}
};

} // namespace aw::graphics
#endif//aw_internal_logger_h
