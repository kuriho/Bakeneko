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

#include "japanese.h"
#include <string>

namespace jp {
	bool hanzi(__int32 charDecimal) {
		return (charDecimal >= 19968 && charDecimal <= 40864);
	}

	bool hiragana(__int32 charDecimal) {
		return (charDecimal >= 12352 && charDecimal <= 12447);
	}

	std::u32string findRuby(const std::u32string& reading, const std::u32string& trailing, int & offset, int kanjiCnt) {
		std::u32string ruby = U"";
		std::u32string part = reading.substr(offset, reading.length() - offset);

		if (trailing != U"") {
			ruby = part.substr(0, part.find(trailing, kanjiCnt));
		} else {
			ruby = part;
		}

		offset += ruby.length();
		return ruby;
	}

	std::u32string addRuby(std::u32string word, std::u32string reading) {
		std::u32string rubified = U"";
		int offset = 0;
		int readOffset = 0;

		for (std::u32string::const_iterator it = word.begin(); it < word.end(); ++it) {
			rubified += *it;

			if (hanzi(*it)) {
				int kanjiCnt = 1;
				int i = 1;
				std::u32string trailing = U"";

				for (;;++i) {
					if (it + i >= word.end())
						break;

					if (!hiragana(*(it + i)) && trailing != U"") {
						if (!hanzi(*(it + i))) {
							trailing += *(it + i);
							i--;
						}
						break;
					}

					if (!(hanzi(*(it + i)) || (__int32)*(it + i) == 12293)) { //々
						trailing += *(it + i);
						continue;
					}

					kanjiCnt++;
					rubified += *(it + i);
				}

				rubified += U"[" + findRuby(reading, trailing, readOffset, kanjiCnt) + U"]" + trailing;
				readOffset += trailing.length();
				it += (kanjiCnt - 1) + trailing.length();
			}
			else {
				readOffset++;
			}
		}

		return rubified;
	}
}