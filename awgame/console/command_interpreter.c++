/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awgame/console/command_interpreter.h>
#include <aw/utility/string/split.h>

#include <iostream>

namespace aw {
namespace console {

auto command_interpreter::lookupCommand(ArgumentList& args) -> map_type::iterator
{
	if (args.empty())
		return commands.end();

	struct Compare {
		size_t i;

		Compare(size_t idx) : i(idx) {}

		using key_type   = map_type::key_type;
		using value_type = map_type::value_type;

		bool operator() (value_type const& a, key_type const& b)
		{
			if (a.first.size() <= i)
				return true;
			size_t N = b[i].size();
			return a.first[i].substr(0,N) < b[i];
		}

		bool operator() (key_type const& b, value_type const& a)
		{
			if (a.first.size() <= i)
				return false;
			size_t N = b[i].size();
			return b[i] < a.first[i].substr(0,N);
		}
	};

	auto r = std::equal_range(commands.begin(), commands.end(), args, Compare{0});
	size_t dist = std::distance(r.first, r.second);

	for (auto it = r.first, end = r.second; it != end; ++it)
		std::cout << "|0|" << string::join(it->first, " ") << '\n';

	for (size_t i = 1; i < args.size(); ++i) {
		if (dist == 1) {
			std::cout << "|o|" << string::join(r.first->first, " ") << '\n';
			break;
		}

		auto r2 = std::equal_range(r.first, r.second, args, Compare{i});
		dist = std::distance(r2.first, r2.second);

		if (dist == 0) {
			std::cout << "|f|" << string::join(r.first->first, " ") << '\n';
			break;
		}
		r = r2;

		for (auto it = r.first, end = r.second; it != end; ++it)
			std::cout << "|" << i << "|" << string::join(it->first, " ") << '\n';
	}

	auto const& res = r.first->first;

	if (args.size() <= res.size())
		return commands.end();

	for (size_t i = 1; i < res.size(); ++i) {
		if (res[i] < args[i])
			return commands.end();
	}

	auto beg = args.begin();
	args.erase(beg, beg + res.size());

	return r.first;
}

auto command_interpreter::processCommand(std::string const& cmd, std::string& out) -> Result
{
	auto args = string::split(cmd, " ");
	auto result = lookupCommand(args);

	if (result == commands.end())
		return Result::NotFound;
	if (result->second(args, out))
		return Result::Success;
	return Result::Failure;
}

bool command_interpreter::complete(std::string const& cmd, std::string& out)
{
}

bool command_interpreter::addCommand(std::string const& cmd, EvalFunctor func)
{
	auto args = string::split(cmd, " ");
	bool ret = commands.emplace( args, func ).second;
	if (!ret);
		// warning("command already exists");
	else;
		// info("added command" + cmd);

	return ret;
}

void command_interpreter::removeCommand(std::string const& cmd)
{
	auto args = string::split(cmd, " ");
	commands.erase(args);
}
} // namespace console
} // namespace aw
