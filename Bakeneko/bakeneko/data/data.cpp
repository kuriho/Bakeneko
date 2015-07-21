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

#include "data.h"

namespace bakeneko {
	BOOL DataMap::add(Data const& newData) {
		bool added = false;

		if (newData.word != "" && !exists(newData)) {
			m_map_data.push_back(newData);
			added = true;
		};

		return added;
	};

	void DataMap::remove(Data const& data) {
		if (exists(data)) {
			m_map_data.erase(std::find(m_map_data.begin(), m_map_data.end(), data));
		};
	};

	BOOL DataMap::exists(Data const& data) {
		return exists(data.word);
	};

	BOOL DataMap::exists(std::string const& word) {
		return (std::find(m_map_data.begin(), m_map_data.end(), word) != m_map_data.end());
	};

};