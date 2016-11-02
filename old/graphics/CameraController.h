/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_CameraController_
#define _aw_CameraController_

#include <aw/graphics/Controller.h>

namespace aw {
namespace graphics {
//! Class used to control camera movement
class CameraController : public Controller {
public:
	//! Virtual destructor
	virtual ~CameraController()
	{
	}

	virtual bool update() = 0;

};

} // namespace graphics
} // namespace aw
#endif//_aw_CameraController_
