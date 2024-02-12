/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_gui_Screen_h
#define aw_gui_Screen_h
#include <aw/gui/Canvas.h>
namespace aw {
namespace gui {
class Screen : public Canvas {
public:
	Screen() = default;
	virtual ~Screen() = default;
 
	virtual Rect<i32> getClientRect() const
	{
		return getAbsoluteRect();
	}

	/*!
	 * Receives event and broadcasts it to children.
	 * \return
	 *      true if event was consumed.
	 */
	virtual bool onEvent(Event* event)
	{
		broadcast(event);
	}
	
	/*!
	 * For a screen class invalidate() is no-op.
	 */
	virtual void invalidate()
	{
	}

	/*!
	 * Accept a GUI Element Visitor. Used for performing
	 * various operations on Elements and their children.
	 */
	virtual void accept(Visitor& visitor);
};
} // namespace gui
} // namespace aw
#endif //aw_gui_Screen_h
