/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awrts/graphics/logging.h>
#include <awrts/graphics/obj_loader.h>
#include <aw/fileformat/obj/loader.h>
#include <aw/io/input_file_stream.h>
#include <aw/graphics/gl/utility/model/obj.h>

#include <map>
#include <memory>

namespace aw::graphics {

using obj_cache = std::map< fs::path, gl3::model >;

static obj_cache cache;

auto load_obj( fs::path const& path ) -> gl3::model*
{
	auto iter = cache.find( path );
	if (iter == end(cache)) {
		io::input_file_stream file{ path };
		auto mesh = obj::mesh::parse( file );

		iter = cache.insert({path, aw::gl3::model_from_obj(mesh)}).first;
	}
	return &iter->second;
}


} // namespace aw::graphics
