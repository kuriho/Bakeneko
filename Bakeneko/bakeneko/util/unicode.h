/*
** Bakeneko 化け猫
** Copyright 2015 by クリホ https://twitter.com/ch_kuriho
**
** This file is part of Bakeneko.
**
** Bakeneko is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Bakeneko is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Bakeneko.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef UTIL_UNICODE_H
#define UTIL_UNICODE_H

#include <string>
#include <codecvt>


namespace utf {

	//UTF8 <-> UTF32 converter (directly using char32_t is not yet supported by VS2015)
	static std::wstring_convert<std::codecvt_utf8<__int32>, __int32> UC32_CONVERTER;

	std::string    fromWidetoUTF8(const std::wstring& text);
	std::u32string fromUTF8to32(const std::string& utf8String);
	std::string    fromUTF32To8(const std::u32string &utf32String);

}

#endif