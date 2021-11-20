#include "main_window.h"

LRESULT CALLBACK MainWindow::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (msg == WM_NCCREATE) {
		LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>(lparam);
		if (cs != nullptr) {
			MainWindow* self = reinterpret_cast<MainWindow*>(cs->lpCreateParams);
			if (self != nullptr) {
				DWORD error_backup = ::GetLastError();
				::SetLastError(0);
				::SetWindowLongPtrW(hwnd, 0, reinterpret_cast<LONG_PTR>(self));
				DWORD result = ::GetLastError();
				::SetLastError(error_backup);

				if (result) {
					return FALSE;
				} else {
					self->hwnd_ = hwnd;
					return self->OnNcCreate(wparam, lparam);
				}
			}
		}

		return FALSE;
	}

	MainWindow* self = reinterpret_cast<MainWindow*>(::GetWindowLongPtrW(hwnd, 0));
	if (self != nullptr) {
		switch (msg) {
		case WM_CREATE :
			return self->OnCreate(wparam, lparam);
		case WM_DESTROY :
			return self->OnDestroy(wparam, lparam);
		case WM_PAINT :
			return self->OnPaint(wparam, lparam);
		}
	}

	return ::DefWindowProcW(hwnd, msg, wparam, lparam);
}

LRESULT MainWindow::OnNcCreate(WPARAM wparam, LPARAM lparam) {
	return ::DefWindowProcW(hwnd_, WM_NCCREATE, wparam, lparam);
}

LRESULT MainWindow::OnCreate(WPARAM, LPARAM) {
	return 0;
}

LRESULT MainWindow::OnDestroy(WPARAM, LPARAM) {
	::PostQuitMessage(0);
	return 0;
}

LRESULT MainWindow::OnPaint(WPARAM, LPARAM) {
	PAINTSTRUCT ps{ 0 };
	::BeginPaint(hwnd_, &ps);
	{
		Gdiplus::Graphics grp(ps.hdc);
		grp.FillRectangle(
			nexon::util::win32::GdiplusHelper::GetInstance().GetColorBrush("black"),
			Gdiplus::Rect(ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top));

		POINT center{ (ps.rcPaint.left + ps.rcPaint.right) / 2, (ps.rcPaint.top + ps.rcPaint.bottom) / 2 };
		grp.FillRectangle(
			nexon::util::win32::GdiplusHelper::GetInstance().GetColorBrush("yellow"),
			Gdiplus::Rect(center.x - 50, center.y - 50, 100, 100));

		grp.Flush();
	}
	::EndPaint(hwnd_, &ps);

	return 0;
}