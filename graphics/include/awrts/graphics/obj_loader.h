/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_obj_loader_h
#define awrts_obj_loader_h
#include <aw/graphics/gl/model.h>
#include <aw/io/filesystem.h>
#include <aw/types/types.h>
#include <stdexcept>

namespace aw::graphics {

auto load_obj( fs::path const& path ) -> gl3::model*;

} // namespace aw::graphics
#endif//awrts_video_manager_h
