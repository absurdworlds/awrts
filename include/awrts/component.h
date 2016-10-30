/*
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_component_h
#define awrts_component_h
#include <aw/types/types.h>
namespace aw {
namespace rts {
struct component {
	component(entity& ent);
	virtual ~component() = default;

	ent_id entity_id() const { return _id; }

	ent_id _id;
};
} // namespace rts
} // namespace aw
#endif//awrts_component_h
