/*
 * Copyright (C) 2013-2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_unit_type_h
#define awrts_unit_type_h
#include <aw/types/types.h>
#include <aw/types/string_view.h>
#include <string>
namespace aw::rts {

/*
enum UnitMovementType {
	UM_STATIC = 0,
	UM_GROUND,
	UM_SWIMMING,
	UM_AMPHIBIOUS,
	UM_TRACKED,
	UM_WHEELED,
	UM_HOVER,
	UM_HOVER_AMPHIBIOUS,
	UM_AIRBORNE
} movementType;
*/

struct unit_type {
	u32 id = -1;

	// TODO: replace all strings with pointers to
	// "prototypes" — classes that are used to create a concrete instance
	struct {
		std::string name;
		std::string description;
	} text;

	struct {
		std::string model_name;
	} visual;

	struct {
		std::string selection_shape;
	} gui;

	struct {
		u64 hitpoints = 1;
	} combat;

	struct {
		std::string type;
		float height = 0;
		float speed  = 0;
		float acceleration = 0;
		float deceleration = 0;
		float turn_speed   = 0;
		bool  can_reverse  = false;
		float reverse_speed      = 0;
		float reverse_turn_speed = 0;
	} movement;

	struct {
		float width = 0;
	} pathfinding;
};

} // namespace aw::rts
#endif//awrts_unit_type_h
