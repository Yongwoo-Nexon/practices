#ifndef UTIL_WIN32_H_
#define UTIL_WIN32_H_

#include <string>
#include <unordered_map>

#include <Windows.h>
#include <gdiplus.h>

#include "util_common.h"

namespace nexon {
namespace util {
namespace win32 {
template <typename T>
void SafeRelease(T** ppT) {
	if (ppT != nullptr && *ppT != nullptr) {
		ppT->Release();
		(*ppT) = nullptr;
	}
}

HINSTANCE GetExeInstance();
HINSTANCE GetDllInstance();

class GdiplusHelper : public common::Singleton<GdiplusHelper> {
public :
	GdiplusHelper();
	~GdiplusHelper();

	bool AddColorBrush(Gdiplus::Color color, const std::string& alias) noexcept;

	Gdiplus::SolidBrush* GetColorBrush(Gdiplus::Color color);
	Gdiplus::SolidBrush* GetColorBrush(const std::string& alias);

private :
	ULONG_PTR token_;
	Gdiplus::GdiplusStartupInput gpsi_;

	std::unordered_map<COLORREF, Gdiplus::SolidBrush*> color_brushes_;
	std::unordered_map<std::string, Gdiplus::Color> color_brush_aliases_;
};

template <typename T, typename Char>
class _WndClassBuilder {
public :
	explicit _WndClassBuilder() : wndclass_{ 0 } {
	}

	_WndClassBuilder& SetClassExtraSize(int size) {
		wndclass_.cbClsExtra = size;
		return *this;
	}

	_WndClassBuilder& SetWindowExtraSize(int size) {
		wndclass_.cbWndExtra = size;
		return *this;
	}

	_WndClassBuilder& SetBackgroundBrush(HBRUSH brush) {
		wndclass_.hbrBackground = brush;
		return *this;
	}

	_WndClassBuilder& SetCursor(HCURSOR cursor) {
		wndclass_.hCursor = cursor;
		return *this;
	}

	_WndClassBuilder& SetIcon(HICON icon) {
		wndclass_.hIcon = icon;
		return *this;
	}

	_WndClassBuilder& SetInstance(HINSTANCE instance) {
		wndclass_.hInstance = instance;
		return *this;
	}

	_WndClassBuilder& SetMessageHandler(WNDPROC wndproc) {
		wndclass_.lpfnWndProc = wndproc;
		return *this;
	}

	_WndClassBuilder& SetClassName(const Char* const classname) {
		wndclass_.lpszClassName = classname;
		return *this;
	}

	_WndClassBuilder& SetMenuName(const Char* const menuname) {
		wndclass_.lpszMenuName = menuname;
		return *this;
	}

	_WndClassBuilder& SetStyle(int style) {
		wndclass_.style = style;
		return *this;
	}

	virtual T& Build(bool class_register) = 0;

protected :
	T wndclass_;
};

class WndClassBuilderA : public _WndClassBuilder<WNDCLASSA, CHAR> {
public:
	explicit WndClassBuilderA() {
		wndclass_.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
		wndclass_.hInstance = GetExeInstance();

#if defined(MAKEINTRESOURCE)
#pragma push_macro("MAKEINTRESOURCE")
#undef MAKEINTRESOURCE
#define MAKEINTRESOURCE MAKEINTRESOURCEA
#endif // defined(MAKEINTRESOURCE)
		wndclass_.hCursor = ::LoadCursorA(NULL, IDC_ARROW);
		wndclass_.hIcon = ::LoadIconA(NULL, IDI_APPLICATION);
#if defined(MAKEINTRESOURCE)
#undef MAKEINTRESOURCE
#pragma pop_macro("MAKEINTRESOURCE")
#endif // defined(MAKEINTRESOURCE)
	}

	virtual WNDCLASSA& Build(bool class_register) override {
		if (class_register) {
			::RegisterClassA(&wndclass_);
		}
		return wndclass_;
	}
};

class WndClassBuilderW : public _WndClassBuilder<WNDCLASSW, WCHAR> {
public:
	explicit WndClassBuilderW() {
		wndclass_.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
		wndclass_.hInstance = GetExeInstance();

#if defined(MAKEINTRESOURCE)
#pragma push_macro("MAKEINTRESOURCE")
#undef MAKEINTRESOURCE
#define MAKEINTRESOURCE MAKEINTRESOURCEA
#endif // defined(MAKEINTRESOURCE)
		wndclass_.hCursor = ::LoadCursorA(NULL, IDC_ARROW);
		wndclass_.hIcon = ::LoadIconA(NULL, IDI_APPLICATION);
#if defined(MAKEINTRESOURCE)
#undef MAKEINTRESOURCE
#pragma pop_macro("MAKEINTRESOURCE")
#endif // defined(MAKEINTRESOURCE)
	}

	virtual WNDCLASSW& Build(bool class_register) override {
		if (class_register) {
			::RegisterClassW(&wndclass_);
		}
		return wndclass_;
	}
};

#if defined(UNICODE) || defined(_UNICODE)
using WndClassBuilder = WndClassBuilderW;
#else
using WndClassBuilder = WndClassBuilderA;
#endif // defined(UNICODE) || defined(_UNICODE)

WPARAM RunMessageLoopA();
WPARAM RunMessageLoopW();
bool SetClientRectA(HWND hwnd, int width, int height, bool redraw);
bool SetClientRectW(HWND hwnd, int width, int height, bool redraw);

#define FuncDecl(Func, Name) constexpr decltype(Func)* Name = Func
#if defined(UNICODE) || defined(_UNICODE)
FuncDecl(RunMessageLoopW, RunMessageLoop);
FuncDecl(SetClientRectW, SetClientRect);
#else
FuncDecl(RunMessageLoopA, RunMessageLoop);
FuncDecl(SetClientRectA, SetClientRect);
#endif // defined(UNICODE) || defined(_UNICODE)
} // namespace win32
} // namespace util
} // namespace nexon

#endif // UTIL_WIN32_H_