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

#include "bakeneko.h"
#include "ui\window.h"
#include <thread>

bakeneko::Bakeneko Chen;

namespace bakeneko {

int Bakeneko::run(HINSTANCE hInstance) {
	m_hWnd = Window::getWindow().create(hInstance, this, &WindowProc);
	m_taskbar.create(m_hWnd, WINDOWCLASS_NAME);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {				
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

void Bakeneko::fetch(std::wstring word) {
	try {
		//UTF8 Conversion
		int nSize = ::WideCharToMultiByte(CP_UTF8, 0, word.c_str(), (int)word.size(), NULL, 0, NULL, NULL);
		if ( nSize != 0 ) {
			std::string utf8Word;
			utf8Word.resize(nSize);
			::WideCharToMultiByte(CP_UTF8, 0, word.c_str(), (int)word.size(), const_cast<char*>(utf8Word.c_str()), nSize, NULL, NULL);

			if (m_data.add( m_api.lookUp(utf8Word).toData() )) 
				m_taskbar.honk(word);
		}

	} catch (...) { /* obligatory note to handle exceptions later */ }

	isFetching = false; 
	PostMessage(m_hWnd, UM_BACKLOG, NULL, NULL);
}

LRESULT Bakeneko::_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case UM_BACKLOG:
		if (!isFetching && !m_basket.empty()) {
			isFetching = true;
			std::wstring& word = m_basket.front();

			std::thread fetcher(&Bakeneko::fetch, this, word);

			m_basket.pop();
			fetcher.detach();
		}
		break;

	case UM_TRAYICON:
		//@TODO: show main window on LBUTTONUP 
		if (lParam == WM_RBUTTONUP) 
			m_taskbar.showContext(m_hWnd);
		break;

	case WM_COMMAND:
		switch (wParam) {
		case UM_EXPORT:
			if(saveFileDialog()) 
				m_export.export(m_data, m_filepath); 

			break;

		case UM_EXIT:
			SendMessage(hwnd, WM_DESTROY, NULL, NULL);
			break;
		}
		break;

	case WM_CREATE:
		m_hWndNext = SetClipboardViewer(hwnd);
		break;

	case WM_CHANGECBCHAIN:
		if (reinterpret_cast<HWND>(wParam) != m_hWndNext) {
			m_hWndNext = reinterpret_cast<HWND>(wParam);
		}else if (m_hWndNext != NULL) {
			SendMessage(m_hWndNext, uMsg, wParam, lParam);
		}
		break;

	case WM_DRAWCLIPBOARD:
		if (IsClipboardFormatAvailable(CF_UNICODETEXT) && m_hWnd != NULL) {
			OpenClipboard(m_hWnd);
			HGLOBAL		hClipboard  = GetClipboardData(CF_UNICODETEXT);
			WCHAR*		clipWBuffer = (WCHAR*)GlobalLock(hClipboard);

			m_basket.push((std::wstring)clipWBuffer);

			GlobalUnlock(hClipboard);
			CloseClipboard();
		}

		SendMessage(m_hWndNext, uMsg, wParam, lParam);
		PostMessage(m_hWnd, UM_BACKLOG, NULL, NULL);
		break;

	case WM_DESTROY:
		ChangeClipboardChain(hwnd, m_hWndNext);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK Bakeneko::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (WM_NCCREATE == uMsg) {
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
		return TRUE;
	}

	//redirect WindowProc to member function _WindowProc
	return ((Bakeneko*)(GetWindowLongPtr(hwnd, GWLP_USERDATA)))->_WindowProc(hwnd, uMsg, wParam, lParam);
}

bool Bakeneko::saveFileDialog() {
	wchar_t file[1024];
	file[0]	= '\0';

	OPENFILENAME ofn = { sizeof ofn };

	ofn.lpstrFile	= file;
	ofn.nMaxFile	= 1024;
	ofn.lpstrFilter = L"Tab-separated values\0 * .tsv\0\0";
	ofn.lpstrTitle	= L"Save File Dialog";
	ofn.Flags		= OFN_EXPLORER;
	
	GetSaveFileName(&ofn);
	m_filepath = file;

	//@TODO: somehow free up memory consumed by windows shell objects -> open it in a new thread?
	return (m_filepath != L"");
}

} // namespace bakeneko