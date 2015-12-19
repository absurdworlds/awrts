/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */

namespace aw {
namespace gui {
Size Size::makeFixed(i32 x, i32 y)
{
	Size tmp(Fixed);
	tmp.fixed.x = x;
	tmp.fixed.y = y;
	return tmp;		
}

Size Size::makeScalableX(f32 x, i32 y)
{
	Size tmp(ScalableX);
	tmp.scalableX.scale = x;
	tmp.scalableX.coord = y;
	return tmp;		
}

Size Size::makeScalableY(i32 x, f32 y)
{
	Size tmp(ScalableY);
	tmp.scalableX.coord = x;
	tmp.scalableX.scale = y;
	return tmp;		
}

Size Size::makeScalable(i32 x, i32 y)
{
	Size tmp(Scalable);
	tmp.scalableX.x = x;
	tmp.scalableX.y = y;
	return tmp;		
}

Size Size::makeAspectLockedX(f32 y, f32 ratio)
{
	Size tmp(AspectLockedX);
	tmp.aspect.coord = y;
	tmp.aspect.ratio = ratio;
	return tmp;		
}

Size Size::makeAspectLockedY(f32 x, f32 ratio)
{
	Size tmp(AspectLockedY);
	tmp.aspect.coord = x;
	tmp.aspect.ratio = ratio;
	return tmp;		
}

Vector2d<i32> Size::toPixels(Vector2d<i32> parent)
{
	i32 tmp;

	switch (type) {
	case Fixed:
		return Vector2d<i32>(fixed.x, fixed.y);
	case ScalableX:
		return Vector2d<i32>(i32(parent.x * scalableX.scale), scalableX.coord);
	case ScalableY:
		return Vector2d<i32>(scalableX.coord, i32(parent.y * scalableX.scale));
	case Scalable:
		return Vector2d<i32>(i32(parent.x * scalable.x), i32(parent.y * scalable.y));
	case AspectLockedX:
		i32 tmp = parent.y * aspect.coord;
		return Vector2d<i32>(i32(tmp * aspect.ratio), tmp);
	case AspectLockedX:
		i32 tmp = parent.x * aspect.coord;
		return Vector2d<i32>(tmp, i32(tmp * aspect.ratio));
	};

	return Vector2d<i32>;
}

} // namespace gui
} // namespace aw
