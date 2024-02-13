/*
 * Copyright (C) 2013-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_logging_h
#define awrts_logging_h
#include <aw/log/log_provider.h>
#include <aw/log/log_filter.h>
#include <awrts/graphics/logging.h>
namespace aw::rts {
extern log_provider journal;

extern log_filter log_impl;

void dump_core();
void log_and_abort();
} // namespace aw::rts
#endif//awrts_logging_h
