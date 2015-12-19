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

#include <aw/common/types.h>
#include <aw/common/EventListener.h>
#include <aw/math/Rect.h>
#include <aw/gui/Size.h>
#include <aw/gui/KeyboardEvent.h>
#include <aw/gui/MouseEvent.h>
#include <aw/gui/GUIEvent.h>
#include <aw/core/Logger.h>

namespace aw {
namespace gui {
class Canvas;
class Widget;
class Style;
class Visitor;

//! Base class for GUI elements
class Element : public EventListener {
public:
	virtual ~Element() = default;

	/*!
	 * Returns pointer to parent element.
	 */
	virtual Element* getParent() const
	{
		return parent;
	}

	virtual Size getPosition() const
	{
		return position;
	}

	virtual Size getDimensions() const
	{
		return dimensions;
	}

	virtual Vector2d<i32> getAbsolutePosition()
	{
		return getAbsoluteRect().getUpperLeft();
	}

	virtual Rect<i32> getAbsoluteRect() const
	{
		// Absolute rect needs updating (element moved,
		// parent moved, etc)
		if (updateAbsoluteRect)
			recalculateAbsoluteRect();

		return absoluteRect;
	}

	virtual Rect<i32> getClientRect() const
	{
	}

	virtual Style* getStyle() const
	{
		if (!style)
			return parent->getStyle();

		return style;
	}

	virtual void setPosition(Size newPosition)
	{
		position = newPosition;
		invalidate();
	}

	virtual void setDimensions(Size newSize)
	{
		dimensions = newSize;
		invalidate();
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

	virtual void setStyle(Style* newStyle)
	{
		// TODO: if newStyle == parent->style, should it be reset to 0?
		style = newStyle;
		invalidate();
	}


	virtual Canvas* toCanvas() = 0;
	virtual Widget* toWidget() = 0;

	/*!
	 * Accept a GUI Element Visitor. Useful for performing
	 * various operations on Elements and their children.
	 */
	virtual void accept(gui::Visitor& visitor);

	/*!
	 * Receive event.
	 * Most commonly used to receive user input.
	 * \return
	 *      true if event was consumed.
	 */
	virtual bool onEvent(Event* event) = 0;

	virtual void invalidate()
	{
		updateAbsoluteRect = true;
	}

	void setName(std::string name)
	{
	}
protected:
	Element()
		: parent(nullptr), updateAbsoluteRect(true)
	{
	}
private:
	void recalculateAbsoluteRect() const
	{
		if (!getParent()) {
			/*absoluteRect = TODO */;
			return;
		}

		// compute parent rect
		Rect<i32> parentRect = parent->getAbsoluteRect();

		i32 height = parentRect.getHeight();
		i32 width  = parentRect.getWidth();

		Vector2d<i32> parentDims(width, height);

		Vector2d<i32> dims = dimensions.toPixels(parentDims);
		Vector2d<i32> pos = position.toPixels(parentDims);

		absoluteRect.upperLeft = parent->getOrigin() + pos;
		absoluteRect.lowerRight = upperLeft + dims;

		updateAbsoluteRect = false;
	}

	Size position;
	Size dimensions;

	mutable bool updateAbsoluteRect;
	mutable Rect<i32> absoluteRect;

	Style* style;
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
