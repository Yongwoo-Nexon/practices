#include "util_win32.h"

namespace nexon {
namespace util {
namespace win32 {
GdiplusHelper::GdiplusHelper() :
	token_{ 0 },
	gpsi_{ 0 } {
	if (Gdiplus::GdiplusStartup(&token_, &gpsi_, nullptr) != Gdiplus::Ok) {
		token_ = 0;
	}
}

GdiplusHelper::~GdiplusHelper() {
	if (token_ != 0) {
		for (auto&& color_brush : color_brushes_) {
			delete color_brush.second;
		}
		color_brushes_.clear();

		Gdiplus::GdiplusShutdown(token_);
		token_ = 0;
	}
}

bool GdiplusHelper::AddColorBrush(Gdiplus::Color color, const std::string& alias) noexcept {
	try {
		Gdiplus::SolidBrush* old_color_brush = GetColorBrush(color);
		Gdiplus::SolidBrush* new_color_brush = new Gdiplus::SolidBrush(color);
		color_brushes_[color.ToCOLORREF()] = new_color_brush;
		delete old_color_brush;
		if (!alias.empty()) {
			color_brush_aliases_[alias] = color;
		}
	}
	catch (...) {
		return false;
	}

	return true;
}

Gdiplus::SolidBrush* GdiplusHelper::GetColorBrush(Gdiplus::Color color) {
	auto&& color_brush_iter = color_brushes_.find(color.ToCOLORREF());

	if (color_brush_iter != color_brushes_.end()) {
		return color_brush_iter->second;
	}

	return nullptr;
}

Gdiplus::SolidBrush* GdiplusHelper::GetColorBrush(const std::string& alias) {
	auto&& color_brush_alias_iter = color_brush_aliases_.find(alias);

	if (color_brush_alias_iter != color_brush_aliases_.end()) {
		return GetColorBrush(color_brush_alias_iter->second);
	}

	return nullptr;
}
} // namespace win32
} // namespace util
} // namespace nexon