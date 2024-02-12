/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_IDType_h
#define aw_IDType_h
namespace aw {
template <typename T, typename Tag>
class IDType {
public:
	typedef T base_type;

	IDType() = default;

	explicit IDType(T newInstance)
		: base(newInstance)
	{
	}

	IDType<T, Tag>& operator = (IDType<T, Tag> other)
	{
		base = other.base;
		return *this;
	}

	bool operator == (IDType<T, Tag> other)
	{
		return base == other.base;
	}

	bool operator < (IDType<T, Tag> other)
	{
		return base < other.base;
	}

	bool operator > (IDType<T, Tag> other)
	{
		return base > other.base;
	}

	explicit operator T&()
	{
		return base;
	}

	explicit operator T const&() const
	{
		return base;
	}
private:
	T base;
};
} // namespace aw
#endif//aw_IDType_h
