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

#include <awrts/version.h>

#include <awrts/map_loader.h>
#include <awrts/players/player.h>
#include <awrts/units/unit_table.h>
#include <awrts/units/unit_factory.h>

namespace aw {
namespace rts {
void update()
{
	journal.info("update()", "Running update.");
	// run game logic
	// run physics
}

void init_video(graphics::video_manager& video)
{
	video.set_window_caption("AWRTS [v0.0.0.0]");
}


bool render(graphics::video_manager& video)
{
	journal.info("render()", "Rendering frame.");
	// send data to renderer process
	if (!video.run())
		return false;

	if (video.is_window_active()) {
		video.begin_render();
		video.end_render();
	}

	return true;
}


int run_game(int c, char const* const* v)
{
	journal.info("main()", "Starting up awrts, build " AWRTS_BUILD_STRING);
	journal.info("main()", "Version: " + to_string(version));

	journal.info("main()", "Initializing graphics subsystem.");

	graphics::journal.set_logger(&log_impl);
	graphics::video_manager video{1066, 600, false, false};
	init_video(video);

	journal.info("main()", "Initializing game components.");
	unit_factory uf{video};
	map_loader mapman{video, uf};
	mapman.load("data/maps/dummy.hdf");

	player pl{video};

	journal.info("main()", "Setting up main loop.");


	bool run = true;

	using namespace std::chrono;
	using namespace std::chrono_literals;

	constexpr intmax_t ticks_per_sec = 60;
	using tick_rate = std::ratio<1, ticks_per_sec>;
	using ticks = duration<i64, tick_rate>;

	journal.info("main()", "Main loop start.");
	// std::cout << tick_time.count() << "\n";

	// TODO: temporary
	log_impl.set_source_filter( [] (string_view s) {
		return s.find("update") == s.npos && s.find("render") == s.npos;
	} );
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

		run = render(video);
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
