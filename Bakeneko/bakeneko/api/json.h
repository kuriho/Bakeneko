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

#ifndef BAKENEKO_API_JSON_H
#define BAKENEKO_API_JSON_H

#include <string>
#include <vector>
#include <map>

namespace bakeneko {
	class JSONBlob {
	public:
		std::map< int, std::map< std::string, std::vector<std::string> > > m_data;

		JSONBlob() { };

		void add(int index, std::string const& key, std::string value);
		std::string get(int pos, std::string const& key, std::string const& elem);
		std::string get(int pos, std::string const& key);

	private:
		std::string findElem(std::string jsonStr, std::string elem);
	};

	class JSONParserLite {
	public:
		JSONParserLite() { };
		~JSONParserLite() { };

		JSONBlob parse(std::string& json);
	};
} // namespace bakeneko

#endif