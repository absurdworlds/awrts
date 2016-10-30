/*
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_entity_list_h
#define awrts_entity_list_h
#include <aw/types/types.h>
namespace aw {
namespace rts {
struct entity_list {
	entity* get(ent_id id)
	{
		if (id.idx > list.size())
			return nullptr;
		auto* ent = list[id.index];
		if (!ent || !compare_id(*ent, id))
			return nullptr;
		return ent;
	}

	entity* remove(ent_id id)
	{
		auto obj = get(id);
		if (obj) {
			list[id.index] = nullptr;
			freelist.push_back(ent->id());
		}
		return obj;
	}

	class access {
		friend struct entity;

		index insert(entity_list& lst, entity& obj)
		{
			return lst.insert(obj);
		}
	};

private:
	friend class access;

	static compare_id(entity& obj, ent_id id)
	{
		index oid = obj.id();
		return oid.version == id.version;
	}

	index insert(entity& obj)
	{
		if (freelist.empty()) {
			index id{list.size() - 1, 0};
			obj.set_id(id);
			list.emplace_back(&obj);
			return id;
		}

		auto id = freelist.back();
		freelist.pop_back();

		++id.version;

		list[id.idx] = &obj;

		return id;
	}

	std::vector<T*>    list;
	std::vector<index> freelist;
};
} // namespace rts
} // namespace aw
#endif//awrts_entity_list_h
