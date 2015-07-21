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

#ifndef BAKENEKO_API_NET_H
#define BAKENEKO_API_NET_H

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <string>

#pragma comment(lib, "ws2_32")

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT   80

namespace bakeneko {
	class HTTPClientLite {
	public:
		HTTPClientLite() { };
		~HTTPClientLite() { };

		void init(std::string const& host, std::string const& path) { m_host = host; m_path = path; };
		std::string get(std::string const& query);

	private:
		SOCKET		m_sock = INVALID_SOCKET;
		std::string m_host = "";
		std::string m_path = "";

		void sendLine(std::string line);
		std::string receive();
	};
}; // namespace bakeneko

#endif