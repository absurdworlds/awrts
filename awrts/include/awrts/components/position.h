/*
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_components_position_h
#define awrts_components_position_h
#include <awrts/component.h>
#include <aw/math/vector3.h>
#include <aw/math/quaternion.h>
namespace aw::rts {
struct position_component : component {
	vector3d<f32>   position;
	quaternion<f32> orientation;
};

} // namespace aw::rts
#endif//awrts_components_position_h
