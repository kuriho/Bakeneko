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

#include <Windows.h>
#include "window.h"

namespace bakeneko {

Window::~Window() { 
	PostQuitMessage(WM_DESTROY); 
	UnregisterClass(WINDOWCLASS_NAME, m_hInstance);
	DestroyWindow(m_hWnd);
}

Window& Window::getWindow() {
	static Window inst;
	return inst;
}

HWND Window::create(HINSTANCE hInstance, LPVOID app, WNDPROC const& wndProc) {
	m_hInstance         = hInstance;

	WNDCLASSEX wclx     = { 0 };
	wclx.cbSize         = sizeof(wclx);
	wclx.lpfnWndProc    = wndProc;
	wclx.hInstance      = hInstance;
	wclx.lpszClassName  = WINDOWCLASS_NAME;
	RegisterClassEx(&wclx);

	return m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, WINDOWCLASS_NAME, 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, hInstance, app);
}

} // namespace bakeneko

