#ifndef H_GLCONTEXT__
#define H_GLCONTEXT__

#include "Window.h"
#include <gl/gl.h>
#include <gl/glu.h>

class GLContext {
public:
	GLContext(Window const& window);
	~GLContext();

	void			setDefaultParameters();
	void			flush();

private:
	bool			initRenderContext();

	Window const&	_window;
	HGLRC			_hrc;
};

#endif