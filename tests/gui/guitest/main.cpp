#include <memory>

#include <Irrlicht/IrrlichtDevice.h>

#include <aw/gui/Element.h>
#include <aw/gui/Window.h>
#include <aw/gui/Drawer.h>
#include <aw/core/Logger.h>

#include <aw/irr/gui/IrrEngine.h>
#include <aw/irr/gui/InputManager.h>

#include <iostream>

namespace irr {
extern "C" IRRLICHT_API IrrlichtDevice* IRRCALLCONV createDevice(
	video::E_DRIVER_TYPE deviceType = video::EDT_SOFTWARE,
	// parantheses are necessary for some compilers
	const core::dimension2d<u32>& windowSize = (core::dimension2d<u32>(640,480)),
	u32 bits = 16,
	bool fullscreen = false,
	bool stencilbuffer = false,
	bool vsync = false,
	IEventReceiver* receiver = 0);
}
namespace aw {
size_t Event::eventTypes;

class Couter : public core::LogBook {
public:
	virtual void log(std::string msg, core::LogLevel level)
	{
		std::cout << msg << std::endl;
	}
};

namespace gui {
// All sruff happens here
int guimain()
{
	/* Init logger*/
	Couter cou;
	core::Logger* log = core::createLogger();
	log->registerLog(&cou);
	core::Logger::setGlobalLogger(log);

	/* Init Irrlicht */
	IrrlichtDevice* device = createDevice(
	                  video::EDT_OPENGL,
	                  irr::core::dimension2d<u32>(800, 600));
	auto driver = device->getVideoDriver();
	auto input = std::make_unique<impl::InputManager>(device);

	/* Init basic gui stuff */
	uptr<Engine> engine = std::make_unique<IrrEngine>(driver);
	Drawer drawer(*engine);

	uptr<Style> style = std::make_unique<Style>();
	Screen canvas = Screen(driver);

	canvas->setStyle(style.get());
	input->registerReceiver(canvas.get());

	/* Create simple window */
	auto window = std::make_unique<Element>("window");
	window->setPosition(Size::makeScalable(0.1,0.1));
	window->setDimensions(Size::makeAspectLockedX(0.8,1.0));

	auto window_ptr = window.get();
	canvas->addElement(std::move(window));

	assert(&*canvas->begin() == window_ptr);


	/* Run stuff */
	while(device->run() && driver)
	if (device->isWindowActive()) {
		driver->beginScene(true, true, irr::video::SColor(255,40,138,155));

		canvas->accept(drawer);

		//device->sleep(1);

		driver->endScene();
	}

	device->drop();
}

} // namespace core
} // namespace aw

int main()
{
	aw::gui::guimain();
}
