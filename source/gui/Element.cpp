/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/utility/range_adaptors.h>
#include <aw/gui/Element.h>
#include <aw/gui/Visitor.h>
#include <aw/core/Logger.h>

namespace aw {
namespace gui {
virtual void Element::recalculateAbsoluteRect() const
{
	bool isFixed = getDimensions().format() == Size::Fixed &&
	               getPosition().format() == Size::Fixed;
	               
	// If size is fixed, then we don't need to do anything
	if (isFixed) {
		Vector2d<i32> dims = getDimensions().toPixels();
		Vector2d<i32> pos = getPosition().toPixels();
		updateAbsoluteRect = false;
		return;
	}

	// We can't calculate absolute rect from relative values
	// if we don't have anything to relate to
	if (!getParent())
		return setAbsoluteRect(Rect<i32>());

	Rect<i32> parentRect = parent->getAbsoluteRect();

	i32 height = parentRect.getHeight();
	i32 width  = parentRect.getWidth();

	Vector2d<i32> parentDims(width, height);

	Vector2d<i32> dims = getDimensions().toPixels(parentDims);
	Vector2d<i32> pos = getPosition().toPixels(parentDims);

	Rect<i32> tmp;
	tmp.upperLeft = parent->getAbsolutePosition() + pos;
	tmp.lowerRight = tmp.upperLeft + dims;

	setAbsoluteRect(tmp);

	updateAbsoluteRect = false;
}

} // namespace gui
} // namespace aw
