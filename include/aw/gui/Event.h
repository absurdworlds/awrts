/*
 * Copyright (C) 2015  hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_gui_Event_
#define _aw_gui_Event_
#include <aw/common/types.h>
namespace aw {
namespace gui {
class Event {
public:
	typedef size_t ID;

	bool is(size_t id)
	{
		return type == id;
	}

	virtual size_t getType()
	{
		return type;
	}
protected:
	static size_t eventTypes;

	Event(size_t type)
		: type(type)
	{
	}
private:
	size_t type;
};

template <class Derived>
class EventId : public Event {
public:
	static size_t id() {
		static size_t type = eventTypes++;
		return type;
	}
protected:
	EventId<Derived>()
		: Event(id())
	{
	}
private:
};

template <class E>
E* event_cast(Event* event) {
	if (event->is(E::type()))
		return static_cast<E*>(event);

	return nullptr;
}
} // namespace gui
} // namespace aw
#endif //_aw_gui_Event_
