﻿/*
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

#ifndef BAKENEKO_API_JISHO_H
#define BAKENEKO_API_JISHO_H

#include "net.h"
#include "json.h"
#include "../data/data.h"

const std::string  API_HOSTNAME   = "jisho.org";
const std::string  API_PATH       = "/api/v1/search/words?keyword=";

const std::string  API_KEY_JP    = "japanese";
const std::string  API_ELEM_WORD = "word";
const std::string  API_ELEM_READ = "reading";
const std::string  API_KEY_POS   = "parts_of_speech";
const std::string  API_KEY_ENG   = "english_definitions";

namespace bakeneko {

class JishoData { 
public:
	std::string              word = "";
	std::vector<std::string> fields;

	JishoData() { };
	~JishoData() { };

	Data        toData(); 
	std::string toString();
};

class JishoAPI {
public:
	JishoAPI(){ m_http.init(API_HOSTNAME, API_PATH); };
	~JishoAPI() { };

	std::vector<Data> lookUp(std::string const& word);

private:
	JSONParserLite m_json;
	HTTPClientLite m_http;
};

}; // namespace bakeneko

#endif