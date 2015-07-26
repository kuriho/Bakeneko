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

JishoData JishoAPI::lookUp(std::string const& word) {
	JSONBlob  json = m_json.parse(m_http.get(word));

	//@TODO: JSON 1:n data
	JishoData data;
	data.word           =  json.get(1, (std::string)"japanese", (std::string)"word");
	data.fields.push_back( json.get(1, (std::string)"japanese", (std::string)"reading") );
	data.fields.push_back( utf::fromUTF32To8( jp::addRuby( utf::fromUTF8to32(data.word), utf::fromUTF8to32(data.fields[0]) ) ) );
	data.fields.push_back( json.get(1, (std::string)"parts_of_speech") );
	data.fields.push_back( json.get(1, (std::string)"english_definitions") );
	//@TODO: additional fields...

	return data; 
}

std::string JishoAPI::addRuby(std::string word, std::string reading) {
	//@TODO: add furigana from word+reading like: ŠÔ‚É‡‚¤ + ‚Ü‚É‚ ‚¤ = ŠÔ[‚Ü]‚É‡[‚ ]‚¤  
	//Reference: http://www.rikai.com/library/kanjitables/kanji_codes.unicode.shtml

	std::string ruby = "";
	return ruby;
}

}; // namespace bakeneko