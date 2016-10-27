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
#include <awrts/logging.h>
#include <aw/utility/unicode/convert.h>

#include <aw/config.h>

#include <Irrlicht/ISceneManager.h>
#if (AW_PLATFORM == AW_PLATFORM_WIN32)
#include <Irrlicht/CIrrDeviceWin32.h>
#elif (AW_PLATFORM_SPECIFIC == AW_PLATFORM_OSX)
#include <Irrlicht/CIrrDeviceMacOSX.h>
#elif (AW_PLATFORM == AW_PLATFORM_POSIX)
#include <Irrlicht/CIrrDeviceLinux.h>
#else
#include <Irrlicht/CIrrDeviceSDL.h>
#endif

using namespace irr;

namespace {

#if (AW_PLATFORM == AW_PLATFORM_WIN32)
IrrlichtDevice* create_irrlicht_device(SIrrlichtCreationParameters& params)
{
	return new CIrrDeviceWin32(params);
}
#elif (AW_PLATFORM_SPECIFIC == AW_PLATFORM_OSX)
IrrlichtDevice* create_irrlicht_device(SIrrlichtCreationParameters& params)
{
	return new CIrrDeviceMacOSX(params);
}
#elif (AW_PLATFORM == AW_PLATFORM_POSIX)
IrrlichtDevice* create_irrlicht_device(SIrrlichtCreationParameters& params)
{
	return new CIrrDeviceLinux(params);
}
#else
IrrlichtDevice* create_irrlicht_device(SIrrlichtCreationParameters& params)
{
	return new CIrrDeviceSDL(params);
}
#endif

} // namespace

namespace aw {
namespace graphics {
video_manager::video_manager(u32 resX, u32 resY, bool fullscreen, bool vsync)
{
	SIrrlichtCreationParameters params;
	params.DriverType = irr::video::EDT_OPENGL;
	params.WindowSize = irr::core::dimension2d<irr::u32>(resX, resY);
	params.Bits       = 32;
	params.Fullscreen = fullscreen;
	params.Stencilbuffer = true;
	params.Vsync         = vsync;
	params.EventReceiver = 0;

	dev = create_irrlicht_device(params);

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

video_manager::~video_manager()
{
	dev->drop();
}

bool video_manager::run()
{
	return dev->run();
}

void video_manager::begin_render()
{
	auto* renderer = dev->getVideoDriver();
	auto* scenemgr = dev->getSceneManager();

	static irr::video::SColor bgcolor{255, 100, 101, 140};
	renderer->beginScene(true, true, bgcolor);
	scenemgr->drawAll();
}

void video_manager::end_render()
{
	auto* renderer = dev->getVideoDriver();
	renderer->endScene();
}

bool video_manager::is_window_active()
{
	return dev->isWindowActive();
}

void video_manager::set_window_caption(string_view caption)
{
	dev->setWindowCaption( unicode::widen(caption).data() );
}

} // namespace graphics
} // namespace aw
