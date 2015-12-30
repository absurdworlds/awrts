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
		: parent(nullptr), updateAbsoluteRect(true)
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

	virtual Rect<i32> getAbsoluteRect() const
	{
		// Absolute rect needs updating (element moved,
		// parent moved, etc)
		if (updateAbsoluteRect)
			recalculateAbsoluteRect();

		return absoluteRect;
	}

	/*!
	 * Causes element's absolute dimensions to be recalculated
	 */
	virtual void invalidate()
	{
		updateAbsoluteRect = true;
		updateClientRect = true;
	}

	/*!
	 * Get currently applied style. If style is unset, then
	 * parent's style is returned.
	 */
	virtual Style* getStyle() const final
	{
		auto style = Canvas::getStyle();
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
protected:
	void setAbsoluteRect(Rect<i32> r) const
	{
		absoluteRect = r;
		updateAbsoluteRect = false;
	}
private:
	friend void Canvas::addElement(uptr<Element>);
	friend uptr<Element> Canvas::removeElement(Element*);

	void setParent(Canvas* newParent)
	{
		parent = newParent;
		invalidate();
	}

	void removeParent()
	{
		parent = nullptr;
		invalidate();
	}

	std::string elementClass;
	std::string suffix;

	/*!
	 * This function defines how absolute rect is calculated
	 */
	virtual void recalculateAbsoluteRect() const;

	/*!
	 * This function defines how client rect is calculated
	 */
	virtual void recalculateClientRect() const;

	Size position;
	Size dimensions;

	mutable bool updateAbsoluteRect;
	mutable Rect<i32> absoluteRect;

	mutable bool updateClientRect;
	mutable Rect<i32> clientRect;

	Canvas* parent;
};
} // namespace gui
} // namespace aw
#endif //_aw_GUIElement_
