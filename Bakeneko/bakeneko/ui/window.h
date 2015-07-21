/*
** Bakeneko �����L
** Copyright 2015 by �N���z https://twitter.com/ch_kuriho
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

#ifndef BAKENEKO_UI_WINDOW_H
#define BAKENEKO_UI_WINDOW_H

#include <Windows.h>

const LPCWSTR WINDOWCLASS_NAME = LR"(Bakeneko)";

namespace bakeneko {

class Window {
public:
	static Window& getWindow();											  //@TODO: add WindowMap [ hWnd : Window& ]
	HWND create(HINSTANCE hInstance, LPVOID app, WNDPROC const& wndProc); //@TODO: add created Window to WindowMap

private:
	HWND	  m_hWnd	  = NULL;
	HINSTANCE m_hInstance = NULL;

	Window() { };
	Window(Window const&) = delete;
	~Window();
	
	void operator=(Window const&) = delete;
};

} // namespace bakeneko
#endif