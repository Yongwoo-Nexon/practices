#include "main_window.h"

MainWindow::MainWindow() :
	hwnd_(NULL) {

}

bool MainWindow::Create() {
	static WNDCLASSW&& wc = std::move(nexon::util::win32::WndClassBuilder()
		.SetClassName(L"MainWindow")
		.SetMessageHandler(&MainWindow::WndProc)
		.SetStyle(CS_VREDRAW | CS_HREDRAW)
		.SetWindowExtraSize(sizeof(this))
		.Build(true));

	HWND hwnd = ::CreateWindowW(
		wc.lpszClassName,
		L"MainWindow",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		NULL,
		NULL,
		wc.hInstance,
		this);

	return !!::IsWindow(hwnd);
}

void MainWindow::Show() {
	if (::IsWindow(hwnd_)) {
		::ShowWindow(hwnd_, SW_SHOW);
	}
}

void MainWindow::Hide() {
	if (::IsWindow(hwnd_)) {
		::ShowWindow(hwnd_, SW_HIDE);
	}
}

void MainWindow::Resize(int width, int height, bool redraw) {
	if (::IsWindow(hwnd_)) {
		nexon::util::win32::SetClientRect(hwnd_, width, height, redraw);
	}
}