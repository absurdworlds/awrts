/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_gui_EventHandler
#define aw_gui_EventHandler
#include <functional>

#include <aw/common/types.h>
#include <aw/common/Event.h>
#include <aw/gui/Element.h>
namespace aw {
namespace gui {

class EventListener {
public:
	typedef std::function<bool(Event*)> EventHandler;

	bool onEvent(Event* event)
	{
		auto handler = getHandler(event.getType());

		if (handler)
			return handler.value()(event);

		return false;
	}

	void setHander(Event::ID id, EventHandler handler)
	{
		handlers[id] = handler;
	}

	opt<EventHandler> getHandler(Event::ID id) const
	{
		auto result = handlers.find(id);

		if (result != std::end(handlers))
			return result->second;

		return nullopt;

	}

	void removeHandler(Event::ID id)
	{
		auto result = handlers.find(id);

		if (result != std::end(handlers))
			handlers.erase(result);
	}

	bool hasHandler(Event::ID id) const
	{
		auto result = handlers.find(id);

		if (result != std::end(handlers))
			return true;

		return false;
	}

private:
	std::unordered_map<Event::ID, EventHandler> handlers;
};

} // namespace gui
} // namespace aw
#endif //aw_gui_EventHandler
