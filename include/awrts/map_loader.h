/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_map_loader_h
#define awrts_map_loader_h
#include <awrts/graphics/video_manager.h>
#include <aw/utility/filesystem.h>

namespace aw::rts {

struct map_loader {
	map_loader(graphics::video_manager& vm)
		: vm{vm}
	{}

	bool load(fs::path const& map_path);

private:
	// FIXME: temportary hack until a permanent solution is implemented
	graphics::video_manager& vm;
};

} // namespace aw:;rts
#endif//awrts_map_loader_h
