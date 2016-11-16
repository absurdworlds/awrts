/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awrts/logging.h>
#include <awrts/graphics/obj_loader.h>
#include <aw/fileformat/obj/loader.h>
#include <aw/io/input_file_stream.h>

#include <Irrlicht/CSceneManager.h>
#include <Irrlicht/SMesh.h>
#include <Irrlicht/SAnimatedMesh.h>
#include <Irrlicht/CMeshBuffer.h>
#include "irr/logger.h"
#include <map>
#include <memory>

using namespace irr;
using namespace irr::scene;
using namespace irr::video;

namespace aw {
namespace graphics {

using obj_cache = std::map< fs::path, SAnimatedMesh* >;

static obj_cache cache;

SAnimatedMesh* load_obj( fs::path const& path )
{
	auto iter = cache.find( path );
	if (iter != end(cache))
		return iter->second;

	io::input_file_stream file{ path };
	auto mesh = obj::mesh::parse( file );

	std::vector< S3DVertex > verts;
	std::vector< unsigned short > faces;

	for (auto face : mesh.faces) {
		for (auto v : face.verts) {
			auto& vp = mesh.verts[ v.index ];
			auto& vn = mesh.normals[ v.normal ];
			auto& vt = mesh.texverts[ v.texuv ];
			verts.emplace_back(
				vp[0], vp[1], vp[2],
				vn[0], vn[1], vn[2],
				SColor(255, 100, 100, 100),
				vt[0], vt[1]
			);
		}
		faces.push_back( verts.size() - 3 );
		faces.push_back( verts.size() - 2 );
		faces.push_back( verts.size() - 1 );
	};

	SMeshBuffer* buf = new SMeshBuffer;
	buf->append( (void const*)verts.data(), verts.size(), faces.data(), faces.size() );
	SMesh* irmesh = new SMesh;
	irmesh->addMeshBuffer( buf );
	irmesh->recalculateBoundingBox();

	SAnimatedMesh* animMesh = new SAnimatedMesh;
	animMesh->addMesh( irmesh );
	animMesh->recalculateBoundingBox();

	cache[path] = animMesh;

	return animMesh;
}


} // namespace graphics
} // namespace aw
