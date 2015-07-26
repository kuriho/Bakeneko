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

#include "jisho.h"
#include "..\util\unicode.h"
#include "..\util\japanese.h"

namespace bakeneko {

Data JishoData::toData() {
	Data data;
	data.word    = word;
	data.strData = toString();
	return data;
}

std::string JishoData::toString() {
	std::string dataString = word;
	
	for (int i = 0; i < fields.size(); ++i) {
		dataString += "\t" + fields[i];
	}

	return dataString;
}

std::vector<Data> JishoAPI::lookUp(std::string const& word) {
	std::vector<Data> result;
	std::vector<int>  relevant = { 1 };

	JSONBlob json = m_json.parse(m_http.get(word));

	//@TODO: Let user decide what fields + which results to grab
	if (json.m_commonIdx.size() != 0)
		relevant = json.m_commonIdx;

	for (int i : relevant) {
		JishoData jishoData;
		jishoData.word =           json.get(i, API_KEY_JP, API_ELEM_WORD, AccessMode::First);
		jishoData.fields.push_back(json.get(i, API_KEY_JP, API_ELEM_READ, AccessMode::First));
		jishoData.fields.push_back(utf::fromUTF32To8(jp::addRuby(utf::fromUTF8to32(jishoData.word), utf::fromUTF8to32(jishoData.fields[0]))));
		jishoData.fields.push_back(json.get(i, API_KEY_POS, AccessMode::First));
		jishoData.fields.push_back(json.get(i, API_KEY_ENG));
		//@TODO: additional fields...

		result.push_back(jishoData.toData());
	}

	return result;
}

}; // namespace bakeneko