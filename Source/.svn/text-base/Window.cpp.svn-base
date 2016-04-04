#include "Window.h"

LRESULT WINAPI msgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch(msg) {

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		break;

		case WM_KEYDOWN:			// quit on esc
			if(wp == VK_ESCAPE)
				PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wp, lp);
}

Window::Window(int width, int height, int bpp, std::string const& title, bool fullscreen) : _hwnd(0), _hdc(0) {

	_width		= width;
	_height		= height;
	_bpp		= bpp;
	_fullscreen	= fullscreen;
	_hwnd		= 0;

	WNDCLASS wc = { CS_HREDRAW | CS_VREDRAW | CS_OWNDC, msgProc, 0, 0, GetModuleHandle(0), 0, 0, 0, 0, "window" };

	if(!RegisterClass(&wc))
		return;

	if(fullscreen) {

		DEVMODE	screenSettings;
	
		ZeroMemory(&screenSettings, sizeof(screenSettings));

		screenSettings.dmSize		= sizeof(screenSettings);
		screenSettings.dmPelsWidth	= _width;
		screenSettings.dmPelsHeight	= _height;
		screenSettings.dmBitsPerPel	= _bpp;
		screenSettings.dmFields		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if(ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			MessageBox(0, "could not init fullscreen", "error", MB_OK);

		ShowCursor(false);
	}

	if(fullscreen)
		_hwnd = CreateWindowEx(	WS_EX_TOOLWINDOW, "window", "",
								WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE, 
								0, 0, _width, _height, 0, 0, GetModuleHandle(0), 0);
	else 
	{
		// 20110501/supah: added centering of window here 
		int xp = (GetSystemMetrics(SM_CXSCREEN) >> 1) - (_width >> 1);
		int yp = (GetSystemMetrics(SM_CYSCREEN) >> 1) - (_height >> 1);

		DWORD style = WS_CAPTION | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE | WS_SYSMENU;
		RECT windowRect = { 0, 0, _width, _height };
		AdjustWindowRect(&windowRect, style, FALSE);

		_hwnd = CreateWindowEx(	WS_EX_APPWINDOW, "window", title.c_str(),
								style, xp, yp, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 0, 0, GetModuleHandle(0), 0);
	}

	if(!_hwnd) {
		MessageBox(0, "could not create window", "error", MB_OK);
		return;
	}

	_hdc = GetDC(_hwnd);
	if(!_hdc) {
		MessageBox(0, "could not get device context", "error", MB_OK);
		return;
	}

	ShowWindow(_hwnd, SW_SHOWNORMAL);
	UpdateWindow(_hwnd);
	SetFocus(_hwnd);
	SetCursor(0);
}

Window::~Window() {

	if(_hdc)
		ReleaseDC(_hwnd, _hdc);

	if(_hwnd)
		DestroyWindow(_hwnd);

	if(_fullscreen) {
		ChangeDisplaySettings(0, 0);
		ShowCursor(true);
	}

	UnregisterClass("window", GetModuleHandle(0));
}

bool Window::active() const {

	MSG	msg;

	while(PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE)) {

		if(msg.message == WM_QUIT)
			return false;

		if(!GetMessage(&msg, 0, 0, 0))
			return true;
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return true;
}

bool Window::fullscreen() const {
	return _fullscreen;
}

int Window::width() const {
	return _width;
}

int Window::height() const {
	return _height;
}

int Window::bpp() const {
	return _bpp;
}

HWND Window::hwnd() const {
	return _hwnd;
}

HDC Window::hdc() const {
	return _hdc;
}

double Window::getFPS() const {

    static int		start		= timeGetTime();
    static int		playtime	= start;
    static int		frames		= 0;
    static double	fps			= 0.0;
	int				now			= timeGetTime() - start;

    if(now >= 1000) {
        fps		= (frames * 1000.0) / (double) (timeGetTime() - start);
        start	= timeGetTime();
		frames	= 0;
    }

    frames++;
    return fps;
}
