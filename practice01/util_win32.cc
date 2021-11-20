#include "util_win32.h"

#pragma comment(lib, "gdiplus.lib")

extern "C" IMAGE_DOS_HEADER __ImageBase;

namespace nexon {
namespace util {
namespace win32 {
HINSTANCE GetExeInstance() {
	return reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr));
}

HINSTANCE GetDllInstance() {
	return reinterpret_cast<HINSTANCE>(&__ImageBase);
}

WPARAM RunMessageLoopA() {
	MSG msg{ 0 };
	while (static_cast<int>(::GetMessageA(&msg, NULL, 0, 0))) {
		::TranslateMessage(&msg);
		::DispatchMessageA(&msg);
	}

	return msg.wParam;
}

WPARAM RunMessageLoopW() {
	MSG msg{ 0 };
	while (static_cast<int>(::GetMessageW(&msg, NULL, 0, 0))) {
		::TranslateMessage(&msg);
		::DispatchMessageW(&msg);
	}

	return msg.wParam;
}

bool SetClientRectA(HWND hwnd, int width, int height, bool redraw) {
	if (::IsWindow(hwnd)) {
		DWORD style = static_cast<DWORD>(::GetWindowLongPtrA(hwnd, GWL_STYLE));
		DWORD exstyle = static_cast<DWORD>(::GetWindowLongPtrA(hwnd, GWL_EXSTYLE));
		BOOL has_menu = ::IsMenu(::GetMenu(hwnd));

		RECT rt{ 0, 0, width, height };
		if (::AdjustWindowRectEx(&rt, style, has_menu, exstyle)) {
			return !!::SetWindowPos(
				hwnd,
				NULL,
				0,
				0,
				rt.right - rt.left,
				rt.bottom - rt.top,
				SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE | (redraw ? 0 : SWP_NOREDRAW));
		}
	}

	return false;
}

bool SetClientRectW(HWND hwnd, int width, int height, bool redraw) {
	if (::IsWindow(hwnd)) {
		DWORD style = static_cast<DWORD>(::GetWindowLongPtrW(hwnd, GWL_STYLE));
		DWORD exstyle = static_cast<DWORD>(::GetWindowLongPtrW(hwnd, GWL_EXSTYLE));
		BOOL has_menu = ::IsMenu(::GetMenu(hwnd));

		RECT rt{ 0, 0, width, height };
		if (::AdjustWindowRectEx(&rt, style, has_menu, exstyle)) {
			return !!::SetWindowPos(
				hwnd,
				NULL,
				0,
				0,
				rt.right - rt.left,
				rt.bottom - rt.top,
				SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE | (redraw ? 0 : SWP_NOREDRAW));
		}
	}

	return false;
}
} // namespace win32
} // namespace util
} // namespace nexon