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
#include <awgame/console/CommandInterpreter.h>
namespace aw {
namespace console {
struct DefaultInterpreter final : Interpreter {
	using Interpreter::Result;
	virtual ~Interpreter() = default;

	Result processCommand(std::string cmd, std::string& out) override;

	using EvalFunc = void(*)(std::string cmd, std::string& out);

private:
	std::map<std::string, EvalFunc> commands;
};
} // namespace console
} // namespace aw
#endif//awgame_DefaultInterpreter_H
