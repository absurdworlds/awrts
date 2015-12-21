/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/gui/Size.h>
namespace aw {
namespace gui {
Size Size::makeFixed(i32 x, i32 y)
{
	Size tmp(Fixed);
	tmp.data[0].i = x;
	tmp.data[1].i = y;
	return tmp;		
}

Size Size::makeScalableX(f32 x, i32 y)
{
	Size tmp(ScalableX);
	tmp.data[0].f = x;
	tmp.data[1].i = y;
	return tmp;		
}

Size Size::makeScalableY(i32 x, f32 y)
{
	Size tmp(ScalableY);
	tmp.data[0].i = x;
	tmp.data[1].f = y;
	return tmp;		
}

Size Size::makeScalable(i32 x, i32 y)
{
	Size tmp(Scalable);
	tmp.data[0].f = x;
	tmp.data[1].f = y;
	return tmp;		
}

Size Size::makeAspectLockedX(f32 y, f32 ratio)
{
	Size tmp(AspectLockedX);
	tmp.data[0].f = ratio;
	tmp.data[1].f = y;
	return tmp;		
}

Size Size::makeAspectLockedY(f32 x, f32 ratio)
{
	Size tmp(AspectLockedY);
	tmp.data[0].f = x;
	tmp.data[1].f = ratio;
	return tmp;		
}

Vector2d<i32> Size::toPixels(Vector2d<i32> parent)
{
	const i32& intX = data[0].i;
	const i32& intY = data[1].i;
	const f32& floatX = data[0].f;
	const f32& floatY = data[1].f;

	i32 tmp;

	switch (type) {
	case Fixed:
		return Vector2d<i32>(intX, intY);
	case ScalableX:
		return Vector2d<i32>(i32(parent.x * floatX), intY);
	case ScalableY:
		return Vector2d<i32>(intX, i32(parent.y * floatY));
	case Scalable:
		return Vector2d<i32>(i32(parent.x * floatX), i32(parent.y * floatY));
	case AspectLockedX:
		tmp = parent.y * floatY;
		return Vector2d<i32>(i32(tmp * floatX), tmp);
	case AspectLockedX:
		tmp = parent.x * floatX;
		return Vector2d<i32>(tmp, i32(tmp * floatY));
	};

	return Vector2d<i32>();
}

} // namespace gui
} // namespace aw
