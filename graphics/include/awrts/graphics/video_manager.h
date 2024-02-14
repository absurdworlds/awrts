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
#include <memory>
#include <stdexcept>
#include <aw/types/types.h>
#include <aw/types/string_view.h>
#include <aw/graphics/gl/command_list.h>
#include <aw/graphics/gl/program.h>

class GLFWwindow;

namespace aw {
namespace gl3 {
struct camera;
} // namespace gl3

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
	video_manager(i32 resX, i32 resY, bool fullscreen, bool vsync);

	video_manager(video_manager const&) = delete;
	video_manager(video_manager&& other) noexcept;

	video_manager& operator=(video_manager const&) = delete;
	video_manager& operator=(video_manager&& other) noexcept;

	~video_manager();

	bool run();
	void begin_render();
	void submit_command(gl3::command_storage cmd);
	void end_render();

	bool is_window_active();
	void set_window_caption(string_view caption);

	gl3::command_list cmds;

private:
	void reshape(int x, int y);

	GLFWwindow* wnd;

	struct context;
	std::unique_ptr<context> ctx;

	std::optional<gl3::program> default_program;
};
} // namespace graphics
} // namespace aw
#endif//awrts_video_manager_h
