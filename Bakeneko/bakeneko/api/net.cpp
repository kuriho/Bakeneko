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
	void HTTPClientLite::sendLine(SOCKET const& sock, std::string const& line) {
		send(sock, line.c_str(), line.length(), 0);
	}

	std::string HTTPClientLite::receive(SOCKET const& sock) {
		std::string resp         = "";
		char buf[DEFAULT_BUFLEN] = {};

		for (;;) {
			int         received = 0;
			std::string respLine = "";

			received = recv(sock, buf, DEFAULT_BUFLEN, 0);
			if (received == 0) break;
			if (received == SOCKET_ERROR) {
				return "";
			}
			resp += respLine.assign(buf, received);
		}

		return resp;
	}

	void HTTPClientLite::removeHeader(std::string & response) {
		if (response != "") {
			int offset = std::string::npos;

			// remove HTTP Header
			if ((offset = response.find_first_of("{", response.find("\r\n\r\n"))) != std::string::npos) {
				response.erase(0, offset);
			}

			// remove trailing noise
			if ((offset = response.find_last_of("}")) != std::string::npos && offset != (response.length() - 1)) {
				response.erase(offset + 1, std::string::npos);
			}
		}
	}

	std::string HTTPClientLite::get(std::string const& query) {
		WSADATA     wsaData;
		SOCKADDR_IN sockAddr = {};

		std::string response = "";
		
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0) {
			static const DWORD timeout = 10000;

			SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

			setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
			setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));

			sockAddr.sin_port = htons(DEFAULT_PORT);
			sockAddr.sin_family = AF_INET;
			sockAddr.sin_addr.s_addr = *((unsigned long*)gethostbyname(m_host.c_str())->h_addr);
			memset(&(sockAddr.sin_zero), 0, 8);

			connect(sock, (SOCKADDR*) &sockAddr, sizeof(sockAddr));

			sendLine(sock, "GET "+ m_path + query + " HTTP/1.1\n");
			sendLine(sock, "Host: " + m_host + "\n");
			sendLine(sock, "User-agent: Bakeneko\n");
			sendLine(sock, "Accept: application/json;q=0.9,text/html;q=0.8,*/*;q=0.7\n");
			sendLine(sock, "Connection: close\n");
			sendLine(sock, "\n");

			response = receive(sock);
			removeHeader(response);

			closesocket(sock);
			WSACleanup();
		}

		return response;
	}
}; // namespace bakeneko