/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_string_as_string_
#define _awrts_string_as_string_
#include <string>
#include <awengine/common/types.h>
namespace awrts {
/*
 * Convert value to string. There may be specializations
 * for other types in their headers.
 */

std::string as_string(int value)
{
	return std::to_string(value);
}

std::string as_string(long value)
{
	return std::to_string(value);
}

std::string as_string(long long value)
{
	return std::to_string(value);
}

std::string as_string(unsigned value)
{
	return std::to_string(value);
}

std::string as_string(unsigned long value)
{
	return std::to_string(value);
}

std::string as_string(unsigned long long value)
{
	return std::to_string(value);
}

std::string as_string(float value)
{
 	return std::to_string(value);
}

std::string as_string(double value)
{
	return std::to_string(value);
}

std::string as_string(long double value)
{
	return std::to_string(value);
}

std::string as_string(char const* value)
{
	return std::string(value);
}

std::string as_string(std::string value)
{
	return value;
}

} // namespace awrts
#endif//_awrts_string_as_string_