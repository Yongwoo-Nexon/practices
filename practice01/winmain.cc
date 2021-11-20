#include "main_window.h"

int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE /*prev_instsance*/, _In_ LPWSTR /*cmdline*/, _In_ int /*cmdshow*/) {
	nexon::util::win32::GdiplusHelper::GetInstance().AddColorBrush(Gdiplus::Color::Black, "black");
	nexon::util::win32::GdiplusHelper::GetInstance().AddColorBrush(Gdiplus::Color::White, "white");
	nexon::util::win32::GdiplusHelper::GetInstance().AddColorBrush(Gdiplus::Color::Yellow, "yellow");

	MainWindow mw;
	if (mw.Create()) {
		mw.Resize(800, 600, false);
		mw.Show();

		return static_cast<int>(nexon::util::win32::RunMessageLoop());
	}

	return 0;
}