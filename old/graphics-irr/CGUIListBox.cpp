/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */

#include <Irrlicht/irrString.h>
#include <Irrlicht/irrList.h>

#include <Irrlicht/IGUIScrollBar.h>
#include <Irrlicht/IGUIListBox.h>

#include <hrengin/common/utf_convert.h>

#include "CGUIListBox.h"

namespace hrengin {
namespace gui {

CGUIListBox::CGUIListBox(irr::gui::IGUIListBox* elem)
	: irrElement_(elem)
{
	elem->grab();
}

CGUIListBox::~CGUIListBox()
{
	irrElement_->drop();
}

u32 CGUIListBox::getId() const
{
	return irrElement_->getID();
}

u32 CGUIListBox::getParentId() const
{
	return irrElement_->getParent()->getID();
}

u32 CGUIListBox::addItem(std::string text)
{
//	irr::core::stringw irrString;
	u32 id = irrElement_->addItem(locale::widen(text).c_str());
	adjustScrollPosition();
	return id;
}

void CGUIListBox::adjustScrollPosition()
{
	// Got this from Irrlicht forums, although I'm not sure it works
	// correctly: irr::core::List::push_back adds an item to the
	// 'Last' position (irr::core::List::push_back gets called when
	// element::addChild is called)
	// Needs testing
	// Damn, why I always so verbose, when it comes to small and simple things?
	irr::core::list<irr::gui::IGUIElement*>::ConstIterator it = irrElement_->getChildren().getLast();
	irr::gui::IGUIScrollBar* scrollbar = static_cast<irr::gui::IGUIScrollBar*>(*it);
	scrollbar->setPos(0x7FFFFFFF);
}


std::string CGUIListBox::getText() const
{
	std::wstring text(irrElement_->getText());
	return locale::narrow(text);
}

void CGUIListBox::setText(std::string text)
{
	irrElement_->setText(locale::widen(text).c_str());
}


} // namespace gui
} // namespace hrengin
