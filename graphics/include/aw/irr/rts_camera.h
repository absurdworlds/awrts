/*
 * Copyright (C) 2014 absurdworlds
 * Copyright (C) 2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_irr_rts_camera_h
#define aw_irr_rts_camera_h
#include <awrts/graphics/video_manager.h>

namespace irr::gui {
class ICursorControl;
}
namespace irr::core {
template<typename T>
class line3d;
}
namespace irr::scene {
class CSceneManager;
class CCameraSceneNode;
}

namespace aw {
namespace graphics {

//! Temporary solution for RTS camera
struct rts_camera {
	rts_camera(irr::scene::CSceneManager* scmgr, irr::gui::ICursorControl* ccon);
	~rts_camera();
	irr::core::line3d<float> cast_ray(int x, int y);


	irr::scene::CSceneManager* scmgr;
	irr::scene::CCameraSceneNode* cam;
};

} // namespace graphics
} // namespace aw
#endif//aw_irr_rts_camera_h
