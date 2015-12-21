/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_gui_Canvas_h
#define aw_gui_Canvas_h
#include <string>
#include <aw/common/types.h>
#include <aw/utility/iterators/Wrapper.h>
#include <aw/math/Rect.h>

#include <aw/common/EventListener.h>

namespace aw {
namespace gui {
class Element;
class Visitor;

//! Base class for GUI elements
class Canvas : public EventListener {
public:
	typedef std::vector<std::unique_ptr<Element>> elements_t;

	Canvas()
		: updateAbsoluteRect(true)
	{
	}

	virtual ~Canvas() = default;
 
	Rect<i32> getAbsoluteRect() const
	{
		// Absolute rect needs updating (element moved,
		// parent moved, etc)
		if (updateAbsoluteRect)
			recalculateAbsoluteRect();

		return absoluteRect;
	}

	Vector2d<i32> getAbsolutePosition() const
	{
		return getAbsoluteRect().getUpperLeft();
	}

	virtual Rect<i32> getClientRect() const
	{
	}

	/*!
	 * List of flags for hitTest method.
	 */
	enum HitTestFlags {
		TestElement = 0b01,
		TestChildren = 0b10,
		TestRecursive = 0b100,
	};

	/*!
	 * Test whether point is within element.
	 * \param flags
	 * 	- 0b01: will test only element,
	 * 	- 0b10: will test only children
	 * 	(by calling hitTest(point, 0b01) for each child),
	 * 	- 0b11: will test both element and children,
	 * 	- 0b110: will test children recursively
	 * 	(by calling hitTest(point 0b111) for each child)
	 * 	- 0b111: will test element and recursively test children
	 */
	bool hitTest(Vector2d<i32> point, HitTestFlags flags = 0b01) const;

	/*!
	 * Get currently applied style
	 */
	virtual Style* getStyle() const
	{
		return style;
	}

	/*!
	 * Set new style
	 */
	void setStyle(Style* newStyle)
	{
		style = newStyle;
		invalidate();
	}

	/*!
	 * Add a child element
	 */
	void addElement(std::unique_ptr<Element> e);

	/*!
	 * Remove child. Returns unique_ptr to detached child,
	 * allowing to rebind it to different object.
	 */
	std::unique_ptr<Element> removeElement(Element* e);
 
	/*!
	 * Get currently active element (which is
	 * currently being interacted with).
	 */
	virtual Element* getActiveElement();

	void bringToFront(Element* e);
	void sendToBack(Element* e);

	/*!
	 * Receive event.
	 * Most commonly used to receive user input.
	 * \return
	 *      true if event was consumed.
	 */
	virtual bool onEvent(Event* event);
	
	/*!
	 * Causes element's absolute dimensions to be recalculated
	 */
	virtual void invalidate()
	{
		updateAbsoluteRect = true;
	}

	void setName(std::string name)
	{
	}

	std::string getName() const
	{
	}

	/*!
	 * Accept a GUI Element Visitor. Used for performing
	 * various operations on Elements and their children.
	 */
	virtual void accept(Visitor& visitor);

	typedef IteratorWrapper<elements_t::iterator, Element> iterator;
	typedef IteratorWrapper<elements_t::const_iterator, Element> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;

	iterator findElement(Element* e);
	const_iterator findElement(Element* e) const;

	auto begin()
	{
		return iterator(std::begin(elements));
	}

	auto end()
	{
		return iterator(std::end(elements));
	}

	auto rbegin()
	{
		return reverse_iterator(std::rbegin(elements));
	}

	auto rend()
	{
		return reverse_iterator(std::rend(elements));
	}

	auto cbegin() const
	{
		return const_iterator(std::cbegin(elements));
	}

	auto cend() const
	{
		return const_iterator(std::cend(elements));
	}

	auto begin() const
	{
		return cbegin();
	}

	auto end() const
	{
		return cend();
	}

	auto crbegin() const
	{
		return const_reverse_iterator(std::crbegin(elements));
	}

	auto crend() const
	{
		return const_reverse_iterator(std::crend(elements));
	}

	auto rbegin() const
	{
		return crbegin();
	}

	auto rend() const
	{
		return crend();
	}
protected:
	void makeActive(Element* element) {
		// TODO: assert(isChild(element));
		active = element;
	}
	Element* getElementFromPoint(Vector2d<i32> point, Vector2d<i32> bounds);

	void setAbsoluteRect(Rect<i32> r) const
	{
		absoluteRect = r;
		updateAbsoluteRect = false;
	}
private:
	/*!
	 * This function defines how absolute rect is calculated
	 */
	virtual void recalculateAbsoluteRect() const = 0;

	mutable bool updateAbsoluteRect;
	mutable Rect<i32> absoluteRect;

	Style* style;

	elements_t::iterator findElement(Element* e);
	bool processEvent(MouseEvent* event);
	bool processEvent(GUIEvent* event);

	elements_t elements;
	Element* active;
	Element* hovered;
};
} // namespace gui
} // namespace aw
#endif //aw_gui_Canvas_h
