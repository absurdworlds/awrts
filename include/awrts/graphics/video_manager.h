/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef awrts_video_manager_h
#define awrts_video_manager_h
#include <stdexcept>
#include <aw/types/types.h>
#include <aw/types/string_view.h>

namespace irr {
class IrrlichtDevice;
namespace video {
class VideoDriver;
}
namespace scene {
class SceneManager;
class AnimatedMesh;
class SceneCollisionManager;
}
} // namespace irr

namespace aw {
namespace graphics {

struct initialization_failure : std::runtime_error {
	initialization_failure(string_view msg)
		: std::runtime_error{
			"failed to initialize graphics: " + std::string(msg)
		}
	{
	}
};

/*! Temporary video manager to initialize Irrlicht engine */
struct video_manager {
	video_manager(u32 resX, u32 resY, bool fullscreen, bool vsync);

	video_manager(video_manager const&) = delete;
	video_manager(video_manager&& other) { std::swap(dev, other.dev); }

	video_manager& operator=(video_manager const&) = delete;
	video_manager& operator=(video_manager&& other) { std::swap(dev, other.dev); }

	~video_manager();

	bool run();
	void begin_render();
	void end_render();

	bool is_window_active();
	void set_window_caption(string_view caption);

	irr::IrrlichtDevice& irr_device() { return *dev; }

private:
	irr::IrrlichtDevice* dev = nullptr;
};
} // namespace graphics
} // namespace aw
#endif//awrts_video_manager_h
