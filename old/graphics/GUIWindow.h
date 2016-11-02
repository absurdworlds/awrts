/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUIWindow_
#define _aw_GUIWindow_

#include <aw/gui/GUIWindow.h>

namespace irr {
namespace gui {
class GUIElement;
}
}

namespace aw {
namespace gui {

class GUIWindow : public GUIWindow {
public:
	GUIWindow(irr::gui::IGUIElement* elem);
	virtual ~GUIWindow();

	virtual u32 getId() const;
	virtual u32 getParentId() const;

	virtual std::string getText() const;
	virtual void setText(std::string text);

	virtual void* getUnderlyingElement() const
	{
		return (void*) irrElement_;
	}

private:
	irr::gui::IGUIElement* irrElement_;
};

} // namespace gui
} // namespace aw
#endif //_aw_GUIWindow_
