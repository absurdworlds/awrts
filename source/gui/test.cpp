#include <aw/gui/GUIEvent.h>
#include <aw/gui/MouseEvent.h>
#include <iostream>

size_t aw::Event::eventTypes;

int main()
{
	using namespace aw::gui;
#if 0
	std::cout << GUIEvent::id() << std::endl;
	std::cout << MouseEvent::id() << std::endl;
#else
	MouseEvent event2;
	GUIEvent event1;
	MouseEvent event3;
	GUIEvent event4;
	std::cout << event1.getType() << std::endl;
	std::cout << event2.getType() << std::endl;
	std::cout << event3.getType() << std::endl;
	std::cout << event4.getType() << std::endl;
#endif
}
