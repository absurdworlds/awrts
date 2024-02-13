/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awgame_console_interpreter_h
#define awgame_console_interpreter_h
#include <aw/types/string_view.h>
namespace aw {
namespace console {
/*!
 * Command interpreter interface for ingame/remote console.
 */
struct interpreter {
	virtual ~interpreter() = default;

	enum class result {
		//! Command was successfully processed
		success,
		//! Command was executed, but there was an error
		failure,
		//! Command was not found
		not_found,
	};

	/*!
	 * Parse string \a cmd and process resulting command.
	 * Messages produced by command are appended to \a out,
	 * \return See enum Result.
	 */
	virtual result execute(string_view cmd, std::string& out) = 0;

	/*!
	 * Complete \a cmd to longest unambiguous string.
	 * \return true if any completion was performed.
	 */
	virtual bool complete(string_view cmd, std::string& out) = 0;
};
} // namespace console
} // namespace aw
#endif//awgame_console_interpreter_h
