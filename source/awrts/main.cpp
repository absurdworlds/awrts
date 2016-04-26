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

namespace aw {
namespace rts {
void update()
{
	// run game logic
	// run physics
}

void render()
{
	// send data to renderer process
}

int main(int c, char const* const* v)
{
	bool run = true;

	// unsure: is it ‘good enough’ to ditch hrengin::getTime()?
	// (hrengin::getTime() is implemented identically to
	// libstc++ and libcxx verison of std::chrono::steady_clock())
	auto time      = std::chrono::high_resolution_clock::now();
	auto prev_time = time;

	using Duration = std::chrono::duration<u64, std::nano>;

	using namespace std::chrono;
	using namespace std::chrono_literals;

	constexpr size_t   ticks     = 60;
	constexpr Duration tick_time = duration_cast<Duration>(1s) / ticks;

	// std::cout << tick_time.count() << "\n";

	Duration elapsed = 0ns;

	while (run) {
		prev_time = time;
		time = std::chrono::high_resolution_clock::now();

		Duration diff = duration_cast<Duration>(time - prev_time);

		// if too much lag occurs, drop frames
		if (diff > 10*tick_time)
			diff = 10*tick_time;

		auto val = diff.count();
		// std::cout << val << " " << tick_time.count() << "\n";

		elapsed += diff;

		while (elapsed >= tick_time) {
			elapsed -= tick_time;
			update();
		}

		render();
	}
}

} // namespace rts
} // namespace aw

int main(int c, char** v)
{
	return aw::rts::main(c,v);
}
