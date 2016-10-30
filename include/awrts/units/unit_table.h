/*
 * Copyright (C) 2013-2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_unit_table_h
#define awrts_unit_table_h
#include <awrts/units/unit_type.h>
#include <unordered_map>
namespace aw {
namespace hdf {
struct Parser;
} // namespace hdf

namespace rts {
//! Table of unit types
struct unit_table {
	void add(unit_type type)
	{
		u32 id = type.id;
		if (table.find(id) == table.end())
			table.emplace(id, std::move(type));
	}

	unit_type const* get(u32 id) const
	{
		auto iter = table.find(id);
		if (iter == table.end())
			return nullptr;
		return &(*iter);
	}

private:
	// TODO: memory pool
	std::unordered_map<u32, unit_type> table;
};

//! load unit types from file
void load_unit_types(unit_table& table, hdf::Parser& file);

} // namespace rts
} // namespace aw
#endif//awrts_unit_table_h
