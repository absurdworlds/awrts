/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awgame_CommandInterpreter_H
#define awgame_CommandInterpreter_H
#include <string>
namespace aw {
namespace console {
/*!
 * Command interpreter interface for ingame/remote console.
 */
struct Interpreter {
	virtual ~Interpreter() = default;

	enum class Result {
		//! Command was successfully processed
		Success,
		//! Command found, but there was an error
		Error,
		//! Command was not found
		NotFound,
	};

	/*!
	 * Parse string \a cmd and process resulting command.
	 * Messages produced by command are appended to \a out,
	 * \return See enum Result.
	 */
	virtual Result processCommand(std::string cmd, std::string& out) = 0;
};
} // namespace console
} // namespace aw
#endif//awgame_CommandInterpreter_H
