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

#ifndef BAKENEKO_UI_TASKBAR_H
#define BAKENEKO_UI_TASKBAR_H

#include <Windows.h>
#include <shellapi.h>
#include <string>

#define UM_TRAYICON (WM_USER+10)
#define UM_EXPORT   (WM_USER+20)
#define UM_SETTINGS (WM_USER+30)
#define UM_ABOUT    (WM_USER+40)
#define UM_BACKLOG  (WM_USER+50)
#define UM_EXIT     (WM_USER+90)

namespace bakeneko {
class Taskbar{
public:
	Taskbar() { };
	~Taskbar() { };

	BOOL create(HWND hwnd, LPCTSTR lpszTip);
	BOOL honk(std::wstring infoText);
	BOOL remove();
	void showContext(HWND hwnd);

private:
	NOTIFYICONDATA m_data;
};
} // namespace bakeneko
#endif