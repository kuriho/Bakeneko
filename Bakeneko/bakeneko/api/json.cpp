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

#include "json.h"
#include <algorithm>
#include <sstream>
#include <regex>
#include "..\util\unicode.h"

namespace bakeneko{
	void JSONBlob::add(int index, std::string const& key, std::string value) {	
		value.erase(std::remove(value.begin(), value.end(), '"'), value.end());
		value.erase(std::remove(value.begin(), value.end(), '\t'), value.end());
		value.erase(std::remove(value.begin(), value.end(), '\n'), value.end());
		value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());

		m_data[index][key].push_back(value);
	}

	std::string JSONBlob::get(int pos, std::string const& key, std::string const& elem, AccessMode mode, int item) {
		if (mode == AccessMode::Exact && item == NULL) return ""; //usage error

		if (m_data.find(pos) != m_data.end()) {
			if (m_data.at(pos).find(key) != m_data.at(pos).end()) {
					return findElem(m_data.at(pos).at(key)[0], elem, mode, item);
			}
		}
		return "";
	}

	std::string JSONBlob::get(int pos, std::string const& key, AccessMode mode, int item) {
		if (mode == AccessMode::Exact && item == NULL) return ""; //usage error

		if (m_data.find(pos) != m_data.end()) {
			if (m_data.at(pos).find(key) != m_data.at(pos).end()) {
				switch (mode) {
				case AccessMode::First:
					item = 1;
					//intentional fallthrough

				case AccessMode::Exact:
					if (item > m_data.at(pos).at(key).size()) {
						return "";
					} else {
						return m_data.at(pos).at(key)[item - 1];
					}

				case AccessMode::All:
					if (m_data.at(pos).at(key).size() == 1) {
						return m_data.at(pos).at(key)[0];
					} else {
						static std::string br = utf::fromWidetoUTF8(L"<br>");
						std::ostringstream os;

						for (int i = 0; i < m_data.at(pos).at(key).size(); ++i) {
							os << m_data.at(pos).at(key)[i];
							if (i != m_data.at(pos).at(key).size() - 1)
								os << br;
						}
						return os.str();
					}
				}
			}
		}
		return "";
	}

	std::string JSONBlob::findElem(std::string jsonStr, std::string elem, AccessMode mode, int item) {
		if (elem == "")	  return jsonStr;
		if (mode == AccessMode::All) return ""; //not required right now
		if (mode == AccessMode::Exact && item == NULL) return ""; //usage error
		if (mode == AccessMode::First) item = 1;

		std::regex  rgx(elem + ":([^,]+),?");
		std::smatch match;
		int counter = 0;

		while (std::regex_search(jsonStr, match, rgx)) {
			counter++;
			if (item == counter) return match[1];
		}

		return "";
	
	}

	JSONBlob JSONParserLite::parse(std::string& json) {
		const std::string is_common = "{\"is_common\":"; 
		const std::regex  rgx("\"(\\w+)\":\\[([^\\[\\]]+)\\]");

		int   begin        = 0;
		int   end          = 0;
		int   dataCounter  = 0;
		std::string common = "";
		
		JSONBlob blob;

		for (;;) {
			std::string data = "";
			std::smatch match;

			if (end > begin) begin = end;

			if (begin == 0) {
				//find first result
				begin = json.find(is_common, begin);
				if (begin == std::string::npos) break;
			}

			//find next result
			end = json.find(is_common, begin + is_common.length());
			if (end == std::string::npos) end = json.length();
			if (end <= begin) break; //EOS

			//optimistically increment dataCounter
			dataCounter++;

			//index common results
			if (json.substr(begin + is_common.length(), 4) == "true") {
				blob.m_commonIdx.push_back(dataCounter);
			}

			data.assign(json, begin, end - begin);

			//flatten JSON
			data.erase(std::remove(data.begin(), data.end(), '{'), data.end());
			data.erase(std::remove(data.begin(), data.end(), '}'), data.end());

			//add data from non-empty JSON arrays to blob
			while(std::regex_search(data, match, rgx)) {
				blob.add(dataCounter, match[1], match[2]);
				data = match.suffix().str();
			}

		}
		return blob;
	}
};