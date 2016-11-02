/*
 * Copyright (C) 2014-2015  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_EventManager_impl_
#define _aw_EventManager_impl_
#include <vector>

#include <aw/platform/time.h>
#include <awrts/game/EventManager.h>
#include <awrts/game/Thinking.h>

namespace aw {
namespace game {
class Thinking;
typedef void (*EventCallback) (u32);

typedef struct {
	union {
		Thinking* owner;
		EventCallback callback;
	};
	u32 nextFire;
	u32 period;
	bool isActive : 1;
	bool isCallback : 1;
} Event;

struct EventManager {
	virtual ~EventManager()
	{

	}
	virtual u32 addEvent(Event event)
	{
		events_.push_back(event);
		return events_.size()-1;
	}
	virtual void removeEvent(u32 eventId)
	{
	}

	virtual void advance();
	{
		u32 time = aw::getTime();

		for (auto event = events_.begin(); event != events_.end(); ++event) {
			if ((*event).nextFire <= time) {
				(*event).owner->think((*event).nextFire);
				(*event).nextFire =  (*event).nextFire + (*event).period;
			}
		}
	}
private:
	std::vector<Event> events_;
};

} // namespace game
} // namespace aw
#endif//_aw_EventManager_impl_
