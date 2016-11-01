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
#include <aw/utility/filesystem.h>
#include <unordered_map>
namespace aw::rts {
//! Table of unit types
struct unit_table {
	void add(unit_type type)
	{
		u32 id = type.id;
		if (table.find(id) == table.cend())
			table.emplace(id, std::move(type));
	}

	unit_type const* get(u32 id) const
	{
		auto iter = table.find(id);
		if (iter == table.cend())
			return nullptr;
		return &(iter->second);
	}

	unit_type const* operator[](string_view id) const
	{
		u32 n = (id[0] << 24) + (id[1] << 16) +
		        (id[2] << 8)  + (id[3] << 0);
		return get(n);
	}

	unit_type const* operator[](u32 id) const
	{
		return get(id);
	}

private:
	/*struct hasher : private std::hash<u32> {
		size_t operator()(unit_type& ut) noexcept
		{
			return std::hash<u32>::operator()(ut.id);
		}
	};
	std::unordered_set<unit_type, hasher> table;
	*/

	// TODO: memory pool
	std::unordered_map<u32, unit_type> table;
};

//! load unit types from file
void load_unit_types(unit_table& table, fs::path const& path);

} // namespace aw::rts
#endif//awrts_unit_table_h
