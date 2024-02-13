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
#include <aw/graphics/gl/awgl/api.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace aw {
namespace graphics {
constexpr GLuint common_block_idx  = 0;
constexpr size_t common_block_size = sizeof(gl3::mat4) + sizeof(gl3::vec3) + sizeof(gl3::vec4);

struct video_manager::context {
	gl3::render_context rc;

	optional<gl3::uniform_buffer> common;
	int hx, hy;
};

video_manager::video_manager(u32 resX, u32 resY, bool fullscreen, bool vsync)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.attributeFlags = sf::ContextSettings::Core;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	auto w = new sf::Window{sf::VideoMode(resX, resY), "", sf::Style::Default, settings};
	wnd.reset( w );
	reshape(resX, resY);

	auto result = ::gl::sys::load_functions_3_3();
	journal.info( "video_manager", "OpenGL loaded" );

	//--------------------
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
}

video_manager::~video_manager()
{
}

bool video_manager::run()
{
	if (!wnd->isOpen())
		return false;
}

void video_manager::begin_render()
{
	gl::clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	cmds.render(ctx->rc);
}

void video_manager::end_render()
{
	gl::use_program( gl::no_program );
}

bool video_manager::is_window_active()
{
	return wnd->hasFocus();
}

void video_manager::set_window_caption(string_view caption)
{
	wnd->setTitle( sf::String::fromUtf8(begin(caption), end(caption)) );
}

void video_manager::reshape(int x, int y)
{
	gl::viewport(0, 0, x, y);

	ctx->hx = x;
	ctx->hy = y;
	if (ctx->rc.active_camera) {
		ctx->rc.active_camera->set_aspect_ratio( float(x) / float(y) );

		auto proj = ctx->rc.active_camera->projection_matrix();
		ctx->common->set_data(0, gl3::array(proj));
	}
}

} // namespace graphics
} // namespace aw
