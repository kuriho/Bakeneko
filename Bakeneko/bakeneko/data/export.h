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

#ifndef BAKENEKO_DATA_EXPORT_H
#define BAKENEKO_DATA_EXPORT_H

#include "data.h"

namespace bakeneko {
	class Exporter {
	public:
		Exporter() { }; 
		~Exporter() { };

		void export(DataMap& data, std::wstring path);
	};
}



#endif