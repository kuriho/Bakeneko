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

#ifndef BAKENEKO_BAKENEKO_H
#define BAKENEKO_BAKENEKO_H

//stop Windows.h from loading winsock.h
#define _WINSOCKAPI_ 

#include <Windows.h>
#include <atomic>
#include <queue>
#include <string>
#include "api\jisho.h"
#include "data\data.h"
#include "data\export.h"
#include "ui\taskbar.h"

namespace bakeneko {

class Bakeneko {
public:
	Bakeneko()  { };
	~Bakeneko() { m_taskbar.remove(); };

	int  run(HINSTANCE hInstance);
	bool saveFileDialog();
	
protected:
	std::atomic<bool> isFetching = false;
	std::queue<std::wstring> m_basket = {};

	void fetch(std::wstring word);

private:
	HWND         m_hWndNext = NULL;
	HWND         m_hWnd = NULL;
	Taskbar      m_taskbar;
	JishoAPI     m_api;
	DataMap      m_data;
	Exporter     m_export;
	std::wstring m_filepath = L"C:/Bakeneko.tsv";

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT _WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

} // namespace bakeneko 

extern bakeneko::Bakeneko Chen;

#endif 
