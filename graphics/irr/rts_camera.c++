/*
 * Copyright (C) 2014 absurdworlds
 * Copyright (C) 2016 Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/irr/rts_camera.h>
#include <aw/irr/CSceneNodeAnimatorCameraRTS.h>

#include <Irrlicht/CSceneManager.h>
#include <Irrlicht/ISceneCollisionManager.h>
#include <Irrlicht/ICursorControl.h>
#include <Irrlicht/CCameraSceneNode.h>

using namespace irr::core;
using namespace irr::scene;
using namespace irr::gui;

namespace aw::graphics {
rts_camera::rts_camera(CSceneManager* scmgr, ICursorControl* ccon)
	: scmgr{scmgr}
{
	cam = scmgr->addCameraSceneNode(0, vector3df{0}, vector3df{0});
	auto animator = new CSceneNodeAnimatorCameraRTS{ccon};
	cam->addAnimator(animator);
	animator->drop();
}

rts_camera::~rts_camera()
{
	cam->remove();
}

line3df rts_camera::cast_ray(int x, int y)
{
	auto* colman = scmgr->getSceneCollisionManager();
	return colman->getRayFromScreenCoordinates(vector2di(x,y), cam);
}
} // namespace aw::graphics
