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

#include "json.h"
#include <algorithm>
#include <regex>

namespace bakeneko{
	void JSONBlob::add(int index, std::string const& key, std::string value) {	
		value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
		m_data[index][key].push_back(value);
	}

	std::string JSONBlob::get(int pos, std::string const& key, std::string const& elem) {
		if (m_data.find(pos) != m_data.end()) {
			if (m_data.at(pos).find(key) != m_data.at(pos).end()) {
				return findElem(m_data.at(pos).at(key)[0], elem);
			}
		}
		return "";
	}

	std::string JSONBlob::get(int pos, std::string const& key) {
		if (m_data.find(pos) != m_data.end()) {
			if (m_data.at(pos).find(key) != m_data.at(pos).end()) {
				return m_data.at(pos).at(key)[0]; 
			}
		}
		return "";
	}

	std::string JSONBlob::findElem(std::string jsonStr, std::string elem) {
		if (elem == "") return jsonStr;

		std::regex	rgx(elem + ":([^,]+),?");
		std::smatch match;
		while (std::regex_search(jsonStr, match, rgx)) {
			return match[1];
		}

		return "";
	
	}

	JSONBlob JSONParserLite::parse(std::string& json) {
		const		std::string is_common = "{\"is_common\":"; 

		int			begin		= 0;
		int			end			= 0;
		int			dataCounter = 0;

		std::regex	rgx("\"(\\w+)\":\\[([^\\[\\]]+)\\]");
		JSONBlob	blob;

		while (1) {
			std::string	data = "";
			std::smatch match;

			if (end > begin) begin = end;

			if (begin == 0) {
				//find first word
				begin = json.find(is_common, begin);
				if (begin == std::string::npos) break;
			}

			//find next word
			end = json.find(is_common, begin + is_common.length());
			if (end == std::string::npos) end = json.length();
			if (end <= begin) break; //EOS

			//only extract common words for now
			if (json.substr(begin+is_common.length(),4) != "true") continue;

			data.assign(json, begin, end - begin);

			//flatten JSON
			data.erase(std::remove(data.begin(), data.end(), '{'), data.end());
			data.erase(std::remove(data.begin(), data.end(), '}'), data.end());

			//optimistically increment dataCounter
			dataCounter++;

			//add data from non-empty JSON arrays to blob
			while(std::regex_search(data, match, rgx)) {
				blob.add(dataCounter, match[1], match[2]);
				data = match.suffix().str();
			}

		}
		return blob;
	}
}