/*
 * Copyright (C) 2014-2016 absurdworlds
 * Copyright (C) 2016      Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <iostream>
#include <awrts/logging.h>


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
			std::string{"failed to initialize graphics: "} + msg
		}
	{
	}
};

/*! Temporary video manager to initialize Irrlicht engine */
struct video_manager {
	video_manager(u32 resX, u32 resY, bool fullscreen);
	~video_manager();

	bool render();
	bool is_window_active();

	irr::IrrlichtDevice& irr_device() { return *dev; }

private:
	irr::IrrlichtDevice* dev;
};


video_manager(u32 resX, u32 resY, bool fullscreen)
{
	SIrrlichtCreationParameters p;
	params.DriverType = irr::video::EDT_OPENGL;
	params.WindowSize = irr::core::dimension2d<irr::u32>(resX, resY);
	params.Bits       = 32;
	params.Fullscreen = fullscreen;
	params.Stencilbuffer = true;
	params.Vsync         = true;
	params.EventReceiver = 0;

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
	dev = new CIrrDeviceWin32(params);
#elif (AW_PLATFORM_SPECIFIC == AW_PLATFORM_OSX)
	dev = new CIrrDeviceMacOSX(params);
#elif (AW_PLATFORM == AW_PLATFORM_POSIX)
	dev = new CIrrDeviceWin32(params);
#else
	dev = new CIrrDeviceSDL(params);
#endif

	dev->setWindowCaption(L"aw A - Irrlicht 1.8.1");

	if (!dev)
		throw initialization_failure{"unable to create Irrlicht device"};

	if (!dev->getVideoDriver()) {
		dev->closeDevice(); // destroy window
		dev->run(); // consume quit message
		dev->drop();
		throw initialization_failure{"unable to initialize OpenGL driver"};
	}

	//settings->setValue("platform.win32.wndHandle", reinterpret_cast<i32>(device_->getVideoDriver()->getExposedVideoData().OpenGLWin32.HWnd));
}

~video_manager()
{
	dev->drop();
}


} // namespace graphics
} // namespace aw
