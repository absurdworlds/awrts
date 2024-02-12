/*
 * Copyright (C) 2016 Hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <unistd.h>
namespace aw {
// 0b 0000 0000 0000
struct TermInfo {
	enum TextAttributes {
		Reset      = 0,
		Bold       = 1,
		Dim        = 2,
		Underscore = 4,
		Inverse    = 8,
	}
	enum TextColor {
		Reset   = 0,
		Set     = 0x8.
			Color   = 0x7,
		Black   = 0x0,
		Red     = 0x1,
		Green   = 0x2,
		Brown   = 0x3,
		Blue    = 0x4,
		Magenta = 0x5,
		Cyan    = 0x6,
		White   = 0x7,
	};
};

char colorNumber(TextColor color)
{
	if (color & Set) {
		switch (color & Color) {
		case ForegroundBlack:
			code[3] = '0';
			break;
		case ForegroundRed:
			code[3] = '1';
			break;
		case ForegroundGreen:
			code[3] = '2';
			break;
		case ForegroundBrown:
			code[3] = '3';
			break;
		case ForegroundBlue:
			code[3] = '4';
			break;
		case ForegroundMagenta:
			code[3] = '5';
			break;
		case ForegroundCyan:
			code[3] = '6';
			break;
		case ForegroundWhite:
			code[3] = '7';
			break;
		}
	} else {
		code[3] = '9';
	}
}

void TermInfo::setBackground(TextAttributes attrib)
{
	char code[10] = "\033[";
	char* cur = &code[2];

	if (attrib & Bold) {
		*cur++ = '1';
	}
	if (attrib & Dim) {
		if (cur > 2) *cur++ = ';';
		*cur++ = '2';
	}
	if (attrib & Underscore) {
		if (cur > 2) *cur++ = ';';
		*cur++ = '4';
	}
	if (attrib & Inverse) {
		if (cur > 2) *cur++ = ';';
		*cur++ = '7';
	}
	*cur++ = 'm';
	*cur = 0;
}

void TermInfo::setBackground(TextColor color)
{
	char code[] = "\033[3xm";
	code[3] = colorNumber(color);
}

void TermInfo::setForeground(TextColor color)
{
	char code[] = "\033[4xm";
	code[3] = colorNumber(color);
}
} // namespace aw
