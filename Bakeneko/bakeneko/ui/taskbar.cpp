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

#include "taskbar.h"
#include "../resource.h"

namespace bakeneko {

BOOL Taskbar::create(HWND hwnd, LPCTSTR lpszTip) {
	m_data.cbSize           = sizeof(NOTIFYICONDATA);
	m_data.hWnd             = hwnd;
	m_data.uID              = UM_TRAYICON;
	m_data.uFlags           = 0|NIF_MESSAGE|NIF_ICON|NIF_TIP;
	m_data.uCallbackMessage = UM_TRAYICON;
	m_data.hIcon            = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	lstrcpyn(m_data.szTip, lpszTip, sizeof(m_data.szTip));

	return !Shell_NotifyIcon(NIM_ADD, &m_data);
}

BOOL Taskbar::honk(std::wstring text) {
	if (text != L"") {
		if (text.size() > 255) {
			text.erase(252, std::wstring::npos);
			text += L"...";
		}

		m_data.uFlags	   = NIF_INFO;
		m_data.dwInfoFlags = NIIF_INFO;
		m_data.uTimeout	   = 500;
		lstrcpy(m_data.szInfo, text.c_str());
		lstrcpy(m_data.szInfoTitle, (LPWSTR)L"HONK! HONK!");
	}
	return !Shell_NotifyIcon(NIM_MODIFY, &m_data);
}

BOOL Taskbar::remove() {
	return !Shell_NotifyIcon(NIM_DELETE, &m_data);
}

void Taskbar::showContext(HWND hwnd) {
	MENUITEMINFO separator = { 0 };
	HMENU        hMenu     = CreatePopupMenu();

	separator.cbSize       = sizeof(MENUITEMINFO);
	separator.fMask        = MIIM_FTYPE;
	separator.fType        = MFT_SEPARATOR;

	if (hMenu) {
		POINT mousePos;

		InsertMenu(hMenu, -1, MF_BYPOSITION,             UM_EXPORT,   L"Export");
		InsertMenuItem(hMenu, -1, FALSE, &separator);
		InsertMenu(hMenu, -1, MF_GRAYED | MF_BYPOSITION, UM_SETTINGS, L"Settings");
		InsertMenu(hMenu, -1, MF_GRAYED | MF_BYPOSITION, UM_ABOUT   , L"About");
		InsertMenuItem(hMenu, -1, FALSE, &separator);
		InsertMenu(hMenu, -1, MF_BYPOSITION,             UM_EXIT    , L"Exit");
		
		GetCursorPos(&mousePos);
		SetForegroundWindow(hwnd);
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, mousePos.x, mousePos.y, 0, hwnd, NULL);
		PostMessage(hwnd, WM_NULL, 0, 0);
		DestroyMenu(hMenu);
	}
}

} //namespace bakeneko
