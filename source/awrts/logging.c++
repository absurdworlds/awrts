/*
 * Copyright (C) 2013-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awrts/logging.h>
#include <aw/log/ostream_logger.h>


#include <cstdlib>
namespace aw {
namespace rts {
log_provider journal;

log_filter log_impl;

void log_and_abort()
{
	std::exception_ptr eptr = std::current_exception();

	if (eptr) try {
		std::rethrow_exception(eptr);
	} catch (std::exception& ex) {
		journal.fatal("terminate()", "caught exception:");
		journal.fatal("terminate()", ex.what() );
	} catch (...) {
		journal.fatal("terminate()", "caught unknown exception");
	}

	std::abort();
}

} // namespace rts
} // namespace aw

#if (AW_SUPPORT_PLATFORM_POSIX)
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#endif

namespace aw {
namespace rts {

void dump_core()
{
#if (AW_SUPPORT_PLATFORM_POSIX)
	int st = 0;
	pid_t pid = fork();

	if (!pid) {
		signal(SIGABRT, SIG_DFL);
		std::abort();
	} else {
		waitpid(pid, &st, 0);
	}
#endif
}

} // namespace rts
} // namespace aw
