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

#include <awrts/logging.h>
#include <aw/log/ostream_logger.h>
#include <aw/types/types.h>

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

int main(int c, char const* const* v)
{
	ostream_logger os{std::cout};
	log_impl.add(os);
	journal.set_logger(&log_impl);

	journal.info("main()", "Initialized logger.");

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

} // namespace rts
} // namespace aw

int main(int c, char** v)
{
	return aw::rts::main(c,v);
}
