/*
 * Copyright (C) 2014-2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awrts/units/unit_table.h>

#include <aw/io/input_file_stream.h>
#include <aw/fileformat/hdf/parser.h>

using namespace std::string_literals;
namespace aw::rts {
namespace {
void parse_text_node(hdf::parser& file, decltype(unit_type::text)& text)
{
	while (auto obj = file.read()) {
		std::string const& name = obj.name;
		if (obj.kind == hdf::object::node) {
			file.skip_node();
			continue;
		}

		if (name == "name") {
			text.name = obj.val.try_get( ""s );
		} else if (name == "description") {
			text.description = obj.val.try_get( ""s );
		}
	}
}

void parse_visual_node(hdf::parser& file, decltype(unit_type::visual)& visual)
{
	while (auto obj = file.read()) {
		std::string const& name = obj.name;
		if (obj.kind == hdf::object::node) {
			file.skip_node();
			continue;
		}
		if (name == "model_name")
			visual.model_name = obj.val.try_get( ""s );
	}
}

void parse_gui_node(hdf::parser& file, decltype(unit_type::gui)& gui)
{
	while (auto obj = file.read()) {
		std::string const& name = obj.name;

		if (obj.kind == hdf::object::node) {
			file.skip_node();
			continue;
		}

		if (name == "selection_shape")
			gui.selection_shape = obj.val.try_get( ""s );
	}
}

void parse_movement_node(hdf::parser& file, decltype(unit_type::movement)& mov)
{
	while (auto obj = file.read()) {
		std::string const& name = obj.name;

		if (obj.kind == hdf::object::node) {
			file.skip_node();
			continue;
		}

		if (name == "type") {
			mov.type = obj.val.try_get( ""s );
		} else if (name == "height") {
			mov.height = obj.val.try_get( 0.0 );
		} else if (name == "height") {
			mov.speed = obj.val.try_get( 0.0 );
		} else if (name == "acceleration") {
			mov.acceleration = obj.val.try_get( 0.0 );
		} else if (name == "deceleration") {
			mov.deceleration = obj.val.try_get( 0.0 );
		} else if (name == "turn_speed") {
			mov.turn_speed = obj.val.try_get( 0.0 );
		} else if (name == "can_reverse") {
			mov.can_reverse = obj.val.try_get( false );
		} else if (name == "reverse_speed") {
			mov.reverse_speed = obj.val.try_get( 0.0 );
		} else if (name == "reverse_turn_speed") {
			mov.reverse_turn_speed = obj.val.try_get( 0.0 );
		}
	}
}

void parse_combat_node(hdf::parser& file, decltype(unit_type::combat)& combat)
{
	while (auto obj = file.read()) {
		std::string const& name = obj.name;
		if (obj.kind == hdf::object::node) {
			file.skip_node();
			continue;
		}

		if (name == "hitpoints") {
			combat.hitpoints = obj.val.try_get( 0ll );
		}
	}
}

void parse_pf_node(hdf::parser& file, decltype(unit_type::pathfinding)& pf)
{
	while (auto obj = file.read()) {
		std::string const& name = obj.name;
		if (obj.kind == hdf::object::node) {
			file.skip_node();
			continue;
		}

		if (name == "width") {
			pf.width = obj.val.try_get( 0.0 );
		}
	}
}

void parse_unit_node(unit_table& table, hdf::parser& file)
{
	unit_type type;

	while (auto obj = file.read()) {
		std::string const& name = obj.name;
		if (obj.kind == hdf::object::node) {
			if (name == "text") {
				parse_text_node(file, type.text);
			} else if (name == "visual") {
				parse_visual_node(file, type.visual);
			} else if (name == "gui") {
				parse_gui_node(file, type.gui);
			} else if (name == "movement") {
				parse_movement_node(file, type.movement);
			} else if (name == "combat") {
				parse_combat_node(file, type.combat);
			} else if (name == "pathfinding") {
				parse_pf_node(file, type.pathfinding);
			} else {
				file.skip_node();
			}
		} else if (obj.kind == hdf::object::value) {
			if (name == "id") {
				std::string const* s = obj.val.get<std::string>();
				if (!s || s->size() < 4) {
					file.skip_node();
					return;
				}
				type.id =
				((*s)[0] << 24) + ((*s)[1] << 16) +
				((*s)[2] << 8)  + ((*s)[3] << 0);
			}
		}
	}

	table.add(type);
}
} // namespace

//! load unit types from file
void load_unit_types(unit_table& table, fs::path const& path)
{
	io::input_file_stream stream{path};
	hdf::parser file{stream};
	hdf::object obj;
	while (file.read(obj)) {
		std::string const& name = obj.name;
		if (obj.kind == hdf::object::node) {
			if (name == "unit") {
				parse_unit_node(table, file);
			} else {
				file.skip_node();
			}
		}
	}
}
} // namespace aw::rts
