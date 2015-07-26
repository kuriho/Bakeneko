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

#ifndef BAKENEKO_DATA_DATA_H
#define BAKENEKO_DATA_DATA_H

#include <Windows.h>
#include <vector>
#include <string>

namespace bakeneko {
	class Data {
	public:
		std::string word;
		std::string strData;

		Data() {};
		~Data() {};

		bool operator== (const Data& data) { return word == data.word; };
		bool operator== (const std::string& newWord) { return word == newWord; };
	};

	class DataMap {
	public:
		std::vector<Data> m_map_data;

		DataMap() { };
		~DataMap() { };

		BOOL add(Data const& newData);
		BOOL add(std::vector<Data> const& newDataList);
		void remove(Data const& data);
		BOOL exists(Data const& data);
		BOOL exists(std::string const& data);
	};

};

#endif