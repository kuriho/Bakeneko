/*
** Bakeneko ‰»‚¯”L
** Copyright 2015 by ƒNƒŠƒz https://twitter.com/ch_kuriho
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

#include <Windows.h>
#include <string>
#include <codecvt>
#include "unicode.h"

namespace utf {

	std::string fromWidetoUTF8(const std::wstring& text) {
		int size = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), (int)text.size(), NULL, 0, NULL, NULL);

		if (size != 0) {
			std::string utf8Word;
			utf8Word.resize(size);
			::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), (int)text.size(), const_cast<char*>(utf8Word.c_str()), size, NULL, NULL);
			return utf8Word;
		}

		return "";
	}

	std::u32string fromUTF8to32(const std::string& utf8String) {
		return reinterpret_cast<const char32_t*>(UC32_CONVERTER.from_bytes(utf8String).data());
	}

	std::string fromUTF32To8(const std::u32string &utf32String) {
		return UC32_CONVERTER.to_bytes(reinterpret_cast<const __int32*>(utf32String.data()));
	}

}