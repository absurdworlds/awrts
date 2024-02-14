/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awrts/graphics/video_manager.h>
#include <awrts/graphics/logging.h>
#include <aw/graphics/gl/render_context.h>
#include <aw/graphics/gl/uniform_buffer.h>
#include <aw/graphics/gl/camera.h>
#include <aw/graphics/gl/awgl/api.h>
#include <aw/graphics/gl/utility/program_loader.h>
#include <aw/graphics/glsl/vec.h>

#include <GLFW/glfw3.h>

namespace aw::graphics {
log_provider journal;

constexpr GLuint common_block_idx  = 0;
constexpr size_t common_block_size = sizeof(gl3::mat4) + sizeof(gl3::vec3) + sizeof(gl3::vec4);

struct video_manager::context {
	gl3::render_context rc;
	gl3::camera* active_camera;
	gl3::camera camera;

	optional<gl3::uniform_buffer> common;
	int hx, hy;
};

static void error_callback(int /*error*/, const char* description)
{
	journal.error( "glfw", description );
}

video_manager::video_manager(i32 resX, i32 resY, bool fullscreen, bool vsync)
{
	glfwInit();

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWmonitor* monitor = nullptr;
	if (fullscreen) {
		monitor = glfwGetPrimaryMonitor();

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		resX = mode->width;
		resY = mode->height;
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	wnd = glfwCreateWindow(resX, resY, "awrts", monitor, nullptr);

	glfwSetWindowUserPointer(wnd, this);
	glfwMakeContextCurrent(wnd);


	auto result = ::gl::sys::load_functions_3_3();
	journal.info( "video_manager", result ?
		"OpenGL loaded" : "Failed to load OpenGL functions" );

	ctx = std::make_unique<context>();


	//--------------------
	// Set default parameters
	// TODO: all this should be the part of the renderer itself
	gl::enable(GL_CULL_FACE);

	gl::cull_face(GL_BACK);
	gl::front_face(GL_CCW);

	gl::enable(GL_DEPTH_TEST);
	gl::depth_mask(GL_TRUE);
	gl::depth_func(GL_LEQUAL);
	gl::depth_range(0.0f, 1.0f);

	gl::clear_color( 1.0f, 1.0f, 1.0f, 1.0f );
	gl::clear_depth( 1.0f );
	gl::clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	auto vsh = gl3::load_shader( gl::shader_type::vertex,   "data/shaders/default.vsh" );
	auto fsh = gl3::load_shader( gl::shader_type::fragment, "data/shaders/default.fsh" );

	std::vector<gl3::shader> shaders;
	if (vsh)
		shaders.push_back(std::move(*vsh));
	if (fsh)
		shaders.push_back(std::move(*fsh));

	gl3::program program;
	program.link(shaders);

	default_program = std::move(program);
	auto block = default_program->uniform_block("common_data");

	GLuint common_block_idx  = 0;
	size_t common_block_size = sizeof(gl3::mat4) + sizeof(gl3::vec3) + sizeof(gl3::vec4);
	ctx->common.emplace(common_block_idx, common_block_size);

	gl3::vec4 lint{ 1.0, 1.0, 1.0, 1.0 };
	gl3::vec3 ldir{ 0.577, 0.577, 0.577 };
	ctx->common->set_data(sizeof(gl3::mat4), lint.array(), ldir.array());
	ctx->active_camera = &ctx->camera;
	ctx->rc.camera_position = math::identity_matrix<float, 4>;

	ctx->common->bind(*default_program, block);


	ctx->camera.set_near_z(0.5f);
	ctx->camera.set_far_z(5000.0f);

	ctx->camera.set_aspect_ratio(1.0f);
	ctx->camera.set_fov( degrees<float>{90} );

	reshape(resX, resY);
}

video_manager::video_manager(video_manager&& other) noexcept
{
	wnd  = other.wnd;
	other.wnd = nullptr;
	ctx  = std::move(other.ctx);
	cmds = std::move(other.cmds);
}

video_manager& video_manager::operator=(video_manager&& other) noexcept
{
	wnd  = other.wnd;
	other.wnd = nullptr;
	ctx  = std::move(other.ctx);
	cmds = std::move(other.cmds);
	return *this;
}

video_manager::~video_manager()
{
}

bool video_manager::run()
{
	glfwPollEvents();
	return !glfwWindowShouldClose(wnd);
}

void video_manager::begin_render()
{
	gl::clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	gl::use_program( gl3::program_handle( *default_program ));
	ctx->rc.set_program(*default_program);

}

void video_manager::submit_command(gl3::command_storage cmd)
{
	cmds.add(std::move(cmd));
}

void video_manager::end_render()
{
	cmds.render(ctx->rc);
	cmds.cmds.clear();

	gl::use_program( gl::no_program );
	glfwSwapBuffers(wnd);
}

bool video_manager::is_window_active()
{
	int focused = glfwGetWindowAttrib(wnd, GLFW_FOCUSED);
	return focused == GLFW_TRUE;
}

void video_manager::set_window_caption(string_view caption)
{
	std::string str(caption);
	glfwSetWindowTitle(wnd, str.data());
}

void video_manager::reshape(int x, int y)
{
	gl::viewport(0, 0, x, y);

	ctx->hx = x;
	ctx->hy = y;
	if (ctx->active_camera) {
		ctx->active_camera->set_aspect_ratio( float(x) / float(y) );

		auto proj = ctx->active_camera->projection_matrix();
		ctx->rc.projection = proj;
		ctx->common->set_data(0, gl3::array(proj));
	}
}

} // namespace aw::graphics
