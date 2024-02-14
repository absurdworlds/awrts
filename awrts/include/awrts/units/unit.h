/*
 * Copyright (C) 2013-2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_unit_h
#define awrts_unit_h
#include <awrts/component.h>
#include <awrts/units/unit_type.h>
#include <aw/graphics/gl/model.h>
#include <aw/graphics/glsl/mat.h>
namespace aw::rts {
struct unit : entity {
	// FIXME: temporary, until graphics component is implemented
	gl3::model* model = nullptr;
	gl3::mat4 transform;
};
} // namespace aw::rts
#endif//awrts_unit_table_h
