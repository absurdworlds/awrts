/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/utility/range_adaptors.h>
#include <aw/gui/Visitor.h>
#include <aw/core/Logger.h>
#include <aw/gui/Canvas.h>
#include <aw/gui/Element.h>

namespace aw {
namespace gui {
namespace {
Canvas::elements_t::iterator
findElementImpl(Canvas::elements_t& elements, Element* e)
{
	auto compare = [&e] (uptr<Element>& ptr) {
		return ptr.get() == e;
	};

	return std::find_if(elements.begin(), elements.end(), compare);
}
}

Canvas::Canvas()
{
}

void Canvas::addElement(std::unique_ptr<Element> e)
{
	core::Logger::debug("[GUI] Canvas: Adding Element");
	e->setParent(this);
	elements.push_back(std::move(e));
}

std::unique_ptr<Element> Canvas::removeElement(Element* e)
{
	core::Logger::debug("[GUI] Canvas: Removing Element");

	auto element = findElementImpl(elements, e);

	if (element == elements.end())
		return nullptr;

	auto temp = std::move(*element);
	temp->removeParent();

	elements.erase(element);

	return std::move(temp);
}

void Canvas::bringToFront(Element* e)
{
	auto element = findElementImpl(elements, e);
	
	if (element == elements.end())
		return;

	auto temp = std::move(*element);
	elements.erase(element);
	elements.push_back(std::move(temp));
}

void Canvas::sendToBack(Element* e)
{
	auto element = findElementImpl(elements, e);
	
	if (element == elements.end())
		return;

	auto temp = std::move(*element);
	elements.erase(element);
	elements.insert(std::begin(elements), std::move(temp));
}

Element* Canvas::getActiveElement()
{
	return active;
}

bool Canvas::broadcast(Event* event)
{
	bool consumed;
	for (auto& elem : elements) {
		consumed = elem->onEvent(event);

		if (consumed)
			return true;
	}

	return consumed;
}

bool Canvas::onEvent(Event* event)
{
/*
	if (event->getType() == MouseEvent::type()) {
		processEvent(event_cast<MouseEvent>(event));
	} else if (event->getType() == GUIEvent::type()) {
		processEvent(event_cast<GUIEvent>(event));
	}

	Element* active = getActiveElement();

	if (!active)
		return false;

	return active->onEvent(event);
	*/
	return false;
}

void Canvas::accept(Visitor& visitor)
{
	visitor.visit(this);
}


Element* Canvas::getElementFromPoint(Vector2d<i32> point, Vector2d<i32> bounds) {
	Element* element = nullptr;
	for (auto& e : make_reverse(elements)) {
		bool within = e->hitTest(point, TestSelf);
		if (within) {
			element = e.get();
			break;
		}
	}
	return element;
}
/*
bool Canvas::processEvent(MouseEvent* event)
{
	auto bounds = event->bounds;
	auto mousePos = Vector2d<i32>(event->position.x() * bounds.x(),
	                 	      event->position.y() * bounds.y());
	auto element = getElementFromPoint(mousePos, bounds);

	switch (event->action) {
	case MouseEvent::Moved: {
			GUIEvent hoveredEvent;
			auto setHovered = [&hoveredEvent, &element, this] {
				hoveredEvent.action = GUIEvent::Hovered;
				element->onEvent(&hoveredEvent);
				this->hovered = element;
			};

			if (element && hovered == element) {
				setHovered();
				break;
			}
			if (hovered) {
				hoveredEvent.action = GUIEvent::Left;
				hovered->onEvent(&hoveredEvent);
				hovered = nullptr;
			}
			if (element)
				setHovered();
			break;
		}
	case MouseEvent::LButtonUp:
				break;
	case MouseEvent::LButtonDown: {
			// If element under cursor is current active
			// element, then we don't need to send any events.
			if (active == element)
				break;

			GUIEvent focusedEvent;
			if (active) {
				focusedEvent.action = GUIEvent::Unfocused;
				active->onEvent(&focusedEvent);
				active = nullptr;
			}
			if (element) {
				focusedEvent.action = GUIEvent::Focused;
				element->onEvent(&focusedEvent);
				active = element;
			}
		}
	default:
		break;
	}

	return false;
}

bool Canvas::processEvent(GUIEvent* event)
{
	switch (event->type()) {
	case GUIEvent::Focused:
		if (getParent()) {
			getParent()->toCanvas()->bringToFront(this);
		}
		return true;
	}
	return false;
}
*/
} // namespace gui
} // namespace aw
