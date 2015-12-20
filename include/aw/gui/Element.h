/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUIElement_
#define _aw_GUIElement_
#include <string>

#include <aw/gui/Canvas.h>
#include <aw/core/Logger.h>

namespace aw {
namespace gui {
//! Base class for GUI elements
class Element : public Canvas {
public:
	Element()
		: parent(nullptr), updateAbsoluteRect(true)
	{
	}
	virtual ~Element() = default;

	/*!
	 * Returns pointer to parent element.
	 */
	virtual Canvas* getParent() const
	{
		return parent;
	}

	void setParent(Element* newParent)
	{
		parent = newParent;
		invalidate();
	}

	void removeParent()
	{
		parent = nullptr;
		invalidate();
	}
private:
	Element* parent;
};

inline bool pointWithinElement(Vector2d<i32> point,
                               Element const& element,
                               Vector2d<i32> screen)
{
	auto rect = element.getAbsoluteRect();
	Rect<i32> screenRect = toPixels(rect, screen);
	return pointWithinRect(point, screenRect);
}

} // namespace gui
} // namespace aw
#endif //_aw_GUIElement_
