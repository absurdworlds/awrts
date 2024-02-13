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
#include <awrts/units/unit_table.h>
#include <awrts/logging.h>

#include <aw/math/vector2d.h>

#include <aw/io/input_file_stream.h>
#include <aw/fileformat/hdf/parser.h>

#include <Irrlicht/IrrlichtDevice.h>
#include <Irrlicht/CSceneManager.h>
#include <Irrlicht/CAnimatedMeshSceneNode.h>
#include <Irrlicht/ISceneCollisionManager.h>

#include <vector>

namespace aw::rts {

static fs::path const model_path = "data/models/";

namespace {
void parse_map_geometry_node(hdf::parser& parser, irr::scene::CSceneManager* scmgr)
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
	SAnimatedMesh* mesh = scmgr->getMesh(path.string().data());
	CAnimatedMeshSceneNode* node = scmgr->addAnimatedMeshSceneNode(mesh);
	// node->addShadowVolumeSceneNode();
}

struct spawn_node {
	std::string type;
	math::vector2d<f32> pos;
	float facing;
};

void parse_unit_node(hdf::parser& parser, std::vector<spawn_node>& out)
{
	spawn_node tmp;
	while (auto obj = parser.read()) {
		hdf::object_kind&  type = obj.kind;
		std::string const& name = obj.name;

		if (type == hdf::object::value) {
			// FIXME: temporary, 
			if (name == "id") {
				if (obj.val.get(tmp.type))
					continue;
			} else if (name == "x") {
				double d;
				if (obj.val.get(d)) {
					tmp.pos[0] = d;
					continue;
				}
			} else if (name == "z") {
				double d;
				if (obj.val.get(d)) {
					tmp.pos[1] = d;
					continue;
				}
			} else if (name == "f") {
				double d;
				if (obj.val.get(d)) {
					tmp.facing = d;
					continue;
				}
			}
			// if any value is invalid — skip whole node,
			// instead of spawning bunch of units at 0,0
			parser.skip_node();
			return;
		} else if (type == hdf::object::node) {
			parser.skip_node();
		}
	}

	out.push_back( tmp );
}

} // namespace

bool map_loader::load(fs::path const& map_path)
{
	io::input_file_stream stream{map_path};
	hdf::parser parser{stream, &log_impl};

	irr::IrrlichtDevice& dev = vm.irr_device();
	irr::scene::CSceneManager* scmgr = dev.getSceneManager();

	// (old TODO: global lighting manager?)
	scmgr->setAmbientLight(irr::video::SColorf(0.35f,0.35f,0.35f,0.35f));

	irr::scene::ILightSceneNode* light = scmgr->addLightSceneNode(0,
		irr::core::vector3df(100, 1000, 100),
		irr::video::SColorf(0.95f, 0.95f, 1.00f, 0.0f), 2800.0f);

	std::vector<spawn_node> units;

	hdf::object obj;
	while (parser.read(obj)) {
		hdf::object_kind&  type = obj.kind;
		std::string const& name = obj.name;
		if (type == hdf::object::node) {
			if (name == "geometry") {
				parse_map_geometry_node(parser, scmgr);
			} else if (name == "unit") {
				parse_unit_node(parser, units);
			} else {
				journal.warning("map_loader", "Unknown node" + name);
				parser.skip_node();
			}
		}
	}

	// TODO: unit types are loaded from gameplay data,
	// which is either located in currently loaded mod,
	// or packed inside map
	unit_table utypes;
	load_unit_types(utypes, "data/units.aw");

	for (auto& node : units) {
		journal.info("map_loader", "Spawning unit " + node.type);
		auto* type = utypes[node.type];
		if (!type) continue;
		auto unit = factory.create_unit(*type);

		// TODO: terrain height
		// ook, hmm, I actually know what to do,
		// there should be a 'map' object with a 'spawn_unit' method
		// (or… dunno, will see)
		float h = type->movement.height;
		unit.node->setPosition({node.pos[0], 0.0f, node.pos[1]});
		unit.node->setRotation({0.0f, node.facing, 0.f});
	}
}

} // namespace aw::rts
