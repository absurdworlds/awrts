/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awrts/map_loader.h>
#include <awrts/logging.h>

#include <aw/io/input_file_stream.h>
#include <aw/fileformat/hdf/parser.h>

#include <Irrlicht/IrrlichtDevice.h>
#include <Irrlicht/ISceneManager.h>
#include <Irrlicht/IAnimatedMeshSceneNode.h>
#include <Irrlicht/ISceneCollisionManager.h>

namespace aw::rts {

static fs::path const model_path = "data/models/";

namespace {
void parse_map_geometry_node(hdf::parser& parser, irr::scene::ISceneManager* scmgr)
{
	using namespace std::string_literals;

	fs::path model_name;
	while (auto obj = parser.read()) {
		hdf::object_kind&  type = obj.kind;
		std::string const& name = obj.name;

		if (type == hdf::object::value) {
			if (name == "model-name")
				model_name = obj.val.try_get( ""s );
		} else if (type == hdf::object::node) {
			parser.skip_node();
		}
	}

	using namespace irr::scene;
	fs::path path = model_path/model_name;
	IAnimatedMesh* mesh = scmgr->getMesh(path.string().data());
	IAnimatedMeshSceneNode* node = scmgr->addAnimatedMeshSceneNode(mesh);
	// node->addShadowVolumeSceneNode();
}
} // namespace

bool map_loader::load(fs::path const& map_path)
{
	io::input_file_stream stream{map_path};
	hdf::parser parser{stream, &log_impl};

	irr::IrrlichtDevice& dev = vm.irr_device();
	irr::scene::ISceneManager* scmgr = dev.getSceneManager();

	// (old TODO: global lighting manager?)
	scmgr->setAmbientLight(irr::video::SColorf(0.35f,0.35f,0.35f,0.35f));

	irr::scene::ILightSceneNode* light = scmgr->addLightSceneNode(0,
		irr::core::vector3df(100, 1000, 100),
		irr::video::SColorf(0.95f, 0.95f, 1.00f, 0.0f), 2800.0f);

	hdf::object obj;
	while (parser.read(obj)) {
		hdf::object_kind&  type = obj.kind;
		std::string const& name = obj.name;
		if (type == hdf::object::node) {
			if (name == "geometry") {
				parse_map_geometry_node(parser, scmgr);
			} else if (name == "unit") {
				//parse_unit_node(parser, scmgr);
				parser.skip_node();
			} else {
				journal.warning("map_loader", "Unknown node" + name);
				parser.skip_node();
			}
		}
	}
}

} // namespace aw::rts
