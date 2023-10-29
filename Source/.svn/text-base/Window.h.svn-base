#ifndef H_WINDOW__
#define H_WINDOW__

#include <windows.h>
#include <string>

class Window {
public:
	Window(int width, int height, int bpp, std::string const& title, bool fullscreen);
	~Window();

	bool		active() const;
	bool		fullscreen() const;

	int			width() const;
	int			height() const;
	int			bpp() const;

	HWND		hwnd() const;
	HDC			hdc() const;

	double		getFPS() const;

private:
	bool		_fullscreen;

	int			_width;
	int			_height;
	int			_bpp;

	HWND		_hwnd;
	HDC			_hdc;
};

#endif