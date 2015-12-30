/*
 * Copyright (C) 2014 absurdworlds
 * Copyright (C) 2015 Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_GUIWindow_
#define _aw_GUIWindow_
#include <aw/gui/Element.h>

namespace aw {
namespace gui {
//! Typical “Window” with a title bar
class Window : public Element {
public:
	Window() = default;
	virtual ~Window() = default;

	virtual bool onEvent(Event* event);
	virtual void accept(Visitor& visitor);

	virtual void setDraggable(bool draggable)
	{
		isDraggable = draggable;
	}

	virtual void invalidate()
	{
		Canvas::invalidate();
		updateClientRect = true;
	}

	bool dragging;
	bool resizing;
	Vector2d<f32> mouseStart;

	bool hasTitlebar;
	bool isDraggable;
};
} // namespace gui
} // namespace aw
#endif //_aw_GUIWindow_
