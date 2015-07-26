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

#include "net.h"

namespace bakeneko {
	void HTTPClientLite::sendLine(std::string line) {
		line += '\n';
		send(m_sock, line.c_str(), line.length(), 0);
	}

	std::string HTTPClientLite::receive() {
		std::string resp         = "";
		char buf[DEFAULT_BUFLEN] = {};

		while(1) {
			int         received = 0;
			std::string respLine = "";

			received = recv(m_sock, buf, DEFAULT_BUFLEN, 0);
			if (received <= 0) break;
			resp += respLine.assign(buf, received);
		}

		return resp;
	}

	std::string HTTPClientLite::get(std::string const& query) {
		WSADATA     wsaData;
		SOCKADDR_IN sockAddr = {};
		int         offset   = std::string::npos;
		std::string response = "";

		if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {
			m_sock = socket(AF_INET, SOCK_STREAM, 0);

			sockAddr.sin_port = htons(DEFAULT_PORT);
			sockAddr.sin_family = AF_INET;
			sockAddr.sin_addr.s_addr = *((unsigned long*)gethostbyname(m_host.c_str())->h_addr);
			memset(&(sockAddr.sin_zero), 0, 8);

			connect(m_sock, (SOCKADDR*) &sockAddr, sizeof(sockAddr));

			sendLine("GET "+ m_path + query + " HTTP/1.1");
			sendLine("Host: " + m_host);
			sendLine("User-agent: Bakeneko");
			sendLine("Accept: application/json;q=0.9,text/html;q=0.8,*/*;q=0.7");
			sendLine("Connection: close");
			sendLine("");

			response = receive();

			// remove HTTP Header
			if ((offset = response.find_first_of("{", response.find("\r\n\r\n"))) != std::string::npos) {
				response.erase(0, offset);	
			}

			// remove trailing noise
			if ((offset = response.find_last_of("}")) != std::string::npos && offset != (response.length() - 1) ) {
				response.erase(offset + 1, std::string::npos);
			}

			closesocket(m_sock);
			WSACleanup();
		}
		return response;
	}
}; // namespace bakeneko