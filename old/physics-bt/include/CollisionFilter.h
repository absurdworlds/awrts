/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_CollisionFilter_
#define _aw_CollisionFilter_
#include <aw/common/types.h>

namespace aw {
namespace physics {
//! Helper struct to filter objects by collision groups
struct CollisionFilter {
	CollisionFilter() = default;
	CollisionFilter(u16 colGroup, u16 bitMask)
		: group(colGroup), mask(bitMask)
	{
	}

	u16 group;
	u16 mask;
};

} // namespace physics
} // namespace aw
#endif//_aw_CollisionFilter_
