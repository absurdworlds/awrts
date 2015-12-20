/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_gui_Container_h
#define aw_gui_Container_h
#include <memory>
#include <aw/utility/iterators/Wrapper.h>

namespace aw {
namespace gui {
class Element;

class Container {
public:
	typedef std::vector<std::unique_ptr<Element>> elements_t;

	Container() = default;
	virtual ~Container() = default;
 
	/*!
	 * Add a child element
	 */
	virtual void addElement(std::unique_ptr<Element> e);

	/*!
	 * Remove child. Returns unique_ptr to detached child,
	 * allowing to rebind it to different object.
	 */
	virtual std::unique_ptr<Element> removeElement(Element* e);
 
	/*!
	 * Get currently active element (which is
	 * currently being interacted with).
	 */
	virtual Element* getActiveElement();

	void bringToFront(Element* e);
	void sendToBack(Element* e);
	virtual bool onEvent(Event* event);
	virtual void accept(Visitor& visitor);

	typedef IteratorWrapper<elements_t::iterator, Element> iterator;
	typedef IteratorWrapper<elements_t::const_iterator, Element> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;

	virtual iterator getFirstChild() const
	{
		return iterator(std::begin(elements));
	}
	virtual iterator getLastChild() const
	{
		return iterator(std::end(elements));
	}

	virtual reverse_iterator rbegin() const
	{
		return reverse_iterator(std::rbegin(elements));
	}
	virtual reverse_iterator rend() const
	{
		return reverse_iterator(std::rend(elements));
	}

	iterator findElement(Element* e) const;

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

private:
	elements_t::iterator findElement(Element* e);
	bool processEvent(MouseEvent* event);
	bool processEvent(GUIEvent* event);

	elements_t elements;
	Element* active;
	Element* hovered;
};
} // namespace gui
} // namespace aw
#endif //aw_gui_Container_h
