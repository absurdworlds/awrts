#include "awrts/map/map.h"
#include "awrts/graphics/logging.h"
#include "aw/graphics/gl/awgl/vertex_func.h"
#include "aw/graphics/gl/render_context.h"
#include "awrts/graphics/obj_loader.h"
#include <awrts/logging.h>

namespace aw::rts {

struct render_unit {
	void operator()( gl3::render_context& ctx )
	{
		auto& model = *u->model;

		gl::bind_vertex_array(model.vao);
		gl3::program& program = *ctx.active_program;

		auto campos = ctx.camera_position;
		program["transform"] = campos * u->transform;

		for (auto obj : model.objects)
			::gl::draw_elements_base_vertex(GL_TRIANGLES, obj.num_elements, GL_UNSIGNED_INT, 0, obj.offset);
	}

	unit* u;
};
struct render_ground {
	void operator()( gl3::render_context& ctx )
	{
		gl::bind_vertex_array(m->vao);
		gl3::program& program = *ctx.active_program;

		auto campos = ctx.camera_position;
		program["transform"] = campos;

		for (auto obj : m->objects)
			::gl::draw_elements_base_vertex(GL_TRIANGLES, obj.num_elements, GL_UNSIGNED_INT, 0, obj.offset);
	}

	gl3::model* m;
};


void map::render(graphics::video_manager& vm)
{
	auto mesh = graphics::load_obj( "data/models/ground.obj" );
	vm.submit_command(render_ground{mesh});
	for (auto& unit : units)
	{
		vm.submit_command(render_unit{&unit});
	}
}
} // namespace aw::rts
