/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_gui_Element_h
#define aw_gui_Element_h
#include <aw/gui/Size.h>
#include <aw/gui/Canvas.h>
namespace aw {
namespace gui {
//! Base class for GUI elements
class Element : public Canvas {
public:
	Element()
		: parent(nullptr)
	{
	}

	virtual ~Element() = default;

	Size getPosition() const
	{
		return position;
	}

	Size getDimensions() const
	{
		return dimensions;
	}

	void setPosition(Size newPosition)
	{
		position = newPosition;
		invalidate();
	}

	void setDimensions(Size newSize)
	{
		dimensions = newSize;
		invalidate();
	}

	/*!
	 * Get currently applied style. If style is unset, then
	 * parent's style is returned.
	 */
	virtual Style* getStyle() const final
	{
		if (!style)
			return parent->getStyle();

		return style;
	}
	
	/*!
	 * Returns pointer to parent element.
	 */
	virtual Canvas* getParent() const
	{
		return parent;
	}
private:
	friend void Canvas::addElement(uptr<Element>);
	friend uptr<Element> Canvas::removeElement(Element*);

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

	virtual void recalculateAbsoluteRect() const;

	Size position;
	Size dimensions;

	Element* parent;
};
} // namespace gui
} // namespace aw
#endif //_aw_GUIElement_
