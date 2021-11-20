#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "util.h"

class MainWindow {
public :
	explicit MainWindow();

	bool Create();

	void Show();
	void Hide();
	void Resize(int width, int height, bool redraw);

private :
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT OnNcCreate(WPARAM, LPARAM);
	LRESULT OnCreate(WPARAM, LPARAM);
	LRESULT OnDestroy(WPARAM, LPARAM);
	LRESULT OnPaint(WPARAM, LPARAM);

private :
	HWND hwnd_;
};

#endif // MAIN_WINDOW_H_