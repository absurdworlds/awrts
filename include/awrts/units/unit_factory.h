/*
 * Copyright (C) 2013-2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_unit_factory_h
#define awrts_unit_factory_h
#include <awrts/units/unit.h>
namespace aw {
namespace graphics {
struct video_manager;
}

namespace rts {
struct unit_factory {
	unit_factory(graphics::video_manager& vm)
		: vm{vm}
	{}
	unit create_unit(unit_type& type);

private:
	graphics::video_manager& vm;
};

} // namespace rts
} // namespace aw
#endif//awrts_unit_factory_h
