/*
 * Copyright (C) 2013-2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/io/filesystem.h>
#include <awrts/units/unit_factory.h>
#include <awrts/graphics/video_manager.h>
#include <awrts/graphics/obj_loader.h>

namespace aw::rts {
static fs::path const model_path = "data/models/units";

unit unit_factory::create_unit(unit_type const& type)
{
	fs::path model_name{type.visual.model_name.begin(), type.visual.model_name.end()};
	fs::path path = model_path/model_name;
	
	using namespace irr;
	using namespace irr::scene;
	auto mesh = graphics::load_obj( path );

	// FIXME: temporary
	unit u;
	//u.node = node;
	return u;
}

} // namespace aw::rts
