/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awgame_command_interpreter_h
#define awgame_command_interpreter_h
#include <map>
#include <functional>
#include <awgame/console/interpreter.h>
#include <aw/types/containers/flat_map.h>
namespace aw {
namespace console {
struct command_interpreter final : interpreter {
	using interpreter::result;
	virtual ~command_interpreter() = default;

	result execute(string_view cmd, std::string& out) override;
	bool complete(string_view cmd, std::string& out) override;

	using ArgumentList = std::vector<string_view>;
	using EvalFunc = bool(ArgumentList const& cmd, std::string& out);
	using EvalFunctor = std::function<EvalFunc>;

	bool add(std::string cmd, EvalFunctor func);
	void remove(std::string cmd);

private:
	using map_type = aw::flat_map<std::string, EvalFunctor>;

	auto lookup(ArgumentList& cmd) -> map_type::iterator;
        map_type commands;
};
} // namespace console
} // namespace aw
#endif//awgame_command_interpreter_h
