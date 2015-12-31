/*
 * Copyright (C) 2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_gui_Visitor_h
#define aw_gui_Visitor_h
namespace aw {
namespace gui {
class Element;

class Canvas;
class Window;

class Widget;
class Button;

/*!
 * Base class for GUI visitor.
 * Visitors are used to perform various operations
 * without adding new methods to class.
 * (see Visitor pattern)
 */
class Visitor {
public:
	virtual ~Visitor() = default;

	virtual void visit(Canvas& element) = 0;
	virtual void visit(Element& element) = 0;
};

} // namespace gui
} // namespace aw
#endif//aw_gui_Visitor_h
