/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_irr_rts_camera_h
#define aw_irr_rts_camera_h
#include <awrts/graphics/video_manager.h>

#include <aw/irr/CSceneNodeAnimatorCameraRTS.h>

#include <Irrlicht/ISceneManager.h>
#include <Irrlicht/ICursorControl.h>
#include <Irrlicht/ICameraSceneNode.h>

namespace aw {
namespace graphics {

//! Temporary solution for RTS camera
struct rts_camera {
	rts_camera(irr::scene::ISceneManager* scmgr, irr::ICursorControl* ccon)
		: scmgr{scmgr}
	{
		using namespace irr::core;
		cam = scmgr->addCameraSceneNode(0, vector3df{0}, vector3df{0});
		auto animator = new CSceneNodeAnimatorCameraRTS{ccon};
		cam->addAnimator(animator);
		animator->drop();
	}

	~rts_camera()
	{
		cam->remove();
	}

	irr::core::line3df cast_ray(int x, int y)
	{
		using namespace irr::scene;
		using namespace irr::core;
		ISceneCollisionManager* colman = scmgr->getSceneCollisionManager();
		return colman->getRayFromScreenCoordinates(vector2di(x,y), cam);
	}

	irr::scene::ISceneManager* scmgr;
	irr::ICameraSceneNode* cam;
};

} // namespace graphics
} // namespace aw
#endif//aw_irr_rts_camera_h
