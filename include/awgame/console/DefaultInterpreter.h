/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awgame_DefaultInterpreter_H
#define awgame_DefaultInterpreter_H
#include <map>
#include <functional>
#include <awgame/console/Interpreter.h>
#include <aw/types/containers/flat_map.h>
namespace aw {
namespace console {
struct DefaultInterpreter final : Interpreter {
	using Interpreter::Result;
	virtual ~DefaultInterpreter() = default;

	Result processCommand(std::string const& cmd, std::string& out) override;
	bool complete(std::string const& cmd, std::string& out) override;

	using ArgumentList = std::vector<std::string>;
	using EvalFunc = bool(ArgumentList const& cmd, std::string& out);
	using EvalFunctor = std::function<EvalFunc>;

	bool addCommand(std::string const& cmd, EvalFunctor func);
	void removeCommand(std::string const& cmd);

private:
	using map_type = aw::flat_map<ArgumentList, EvalFunctor>;

	auto lookupCommand(ArgumentList& cmd) -> map_type::iterator;
        map_type commands;
};
} // namespace console
} // namespace aw
#endif//awgame_DefaultInterpreter_H
