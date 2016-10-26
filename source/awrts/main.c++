/*
 * Copyright (C) 2013-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <iostream>
#include <chrono>
#include <ratio>

#include <aw/types/types.h>

#include <awrts/logging.h>
#include <aw/log/ostream_logger.h>
#include <aw/log/ml_raii_wrapper.h>

#include <awrts/graphics/video_manager.h>

namespace aw {
namespace rts {
void update()
{
	journal.info("update()", "Running update.");
	// run game logic
	// run physics
}

void render()
{
	journal.info("render()", "Rendering frame.");
	// send data to renderer process
}


int run_game(int c, char const* const* v)
{
	journal.info("main()", "Initializing graphics subsystem.");


	graphics::video_manager video{1066, 600, false, true};


	journal.info("main()", "Setting up main loop.");


	bool run = true;

	using namespace std::chrono;
	using namespace std::chrono_literals;

	constexpr intmax_t ticks_per_sec = 60;
	using tick_rate = std::ratio<1, ticks_per_sec>;
	using ticks = duration<i64, tick_rate>;

	journal.info("main()", "Main loop start.");
	// std::cout << tick_time.count() << "\n";

	nanoseconds elapsed = 0ns;

	// TODO:
	// std::chrono::steady_clock() vs high_resolution_clock
	auto time      = high_resolution_clock::now();
	auto prev_time = time;

	while (run) {
		prev_time = time;
		time = high_resolution_clock::now();

		nanoseconds diff = time - prev_time;

		// if too much lag occurs, drop frames
		if (diff > ticks{10}) {
			diff = duration_cast<nanoseconds>(ticks{10});
			journal.warning("main()", "Too much time elapsed since last frame, dropping frames.");
		}

		auto val = diff.count();
		//std::cout << val << " " << duration_cast<nanoseconds>(ticks{1}).count() << "\n";

		elapsed += diff;

		while (elapsed >= ticks{1}) {
			elapsed -= duration_cast<nanoseconds>(ticks{1});
			update();
		}

		render();
	}

	journal.info("main()", "Main loop end.");

	journal.info("main()", "Exiting.");
}

int main(int c, char const* const* v)
{
	raii_log<ostream_logger> os{log_impl, std::cout};

	journal.set_logger(&log_impl);
	journal.info("main()", "Initialized logger.");

	try {
		return run_game(c,v);
	} catch( std::exception& ex ) {
		journal.fatal("main()", "caught exception:");
		journal.fatal("main()", ex.what());

		dump_core();

		return EXIT_FAILURE;
	}
}

} // namespace rts
} // namespace aw


int main(int c, char** v)
{
	return aw::rts::main(c,v);
}
