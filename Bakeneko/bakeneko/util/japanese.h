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

#ifndef UTIL_JAPANESE_H
#define UTIL_JAPANESE_H

#include <string>

namespace jp {

	bool hanzi(__int32 charDecimal);
	bool hiragana(__int32 charDecimal);

	std::u32string findRuby(const std::u32string& reading, const std::u32string& trailing, int & offset, int kanjiCnt);
	std::u32string addRuby(std::u32string word, std::u32string reading);
}

#endif