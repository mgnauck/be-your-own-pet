#include "GLContext.h"

GLContext::GLContext(Window const& window): _window(window), _hrc(0) {
	if(!initRenderContext())
		MessageBox(0, "could not init opengl context", "error", MB_OK);
}

GLContext::~GLContext() {
	if(_hrc) {
		wglMakeCurrent(0, 0);
		wglDeleteContext(_hrc);
	}
}

bool GLContext::initRenderContext() {

	static PIXELFORMATDESCRIPTOR pfd = {

				sizeof(PIXELFORMATDESCRIPTOR),										// size
				1,																	// version
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,			// flags
				PFD_TYPE_RGBA,														// pixeltype
				_window.bpp(),														// colorbits
				0,																	// redbits
				0,																	// redshift
				0,																	// greenbits
				0,																	// greenshift
				0,																	// bluebits
				0,																	// blueshift
				0,																	// alphabits
				0,																	// alphashift
				0,																	// accumbits
				0,																	// accumredbits
				0,																	// accumgreenbits
				0,																	// accumbluebits
				0,																	// accumalphabits
				_window.bpp(),														// depthbits
				8,																	// stencilbits
				0,																	// auxbits
				PFD_MAIN_PLANE,														// layertype
				0,																	// reserved
				0,																	// layermask
				0,																	// visiblemask
				0																	// damagemask
	};

	int pixelFormat = ChoosePixelFormat(_window.hdc(), &pfd);
	if(!pixelFormat) {
		MessageBox(0, "could not find pixel format", "error", MB_OK);
		return false;
	}

	if(!SetPixelFormat(_window.hdc(), pixelFormat, &pfd)) {
		MessageBox(0, "could not set pixel format", "error", MB_OK);
		return false;
	}

	_hrc = wglCreateContext(_window.hdc());
	if(!_hrc) {
		MessageBox(0, "could not create render context", "error", MB_OK);
		return false;
	}

	if(!wglMakeCurrent(_window.hdc(), _hrc)) {
		MessageBox(0, "could not make render context current", "error", MB_OK);
		return false;
	}

	return true;
}

void GLContext::setDefaultParameters() {
	// some default shit for fixed function pipeline
	glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_LINE);
	
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glDepthMask(true);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(255.0);
	glEnable(GL_DEPTH_TEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glEnable(GL_NORMALIZE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, false);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


#define GL_LIGHT_MODEL_COLOR_CONTROL_EXT	0x81F8
#define GL_SINGLE_COLOR_EXT					0x81F9
#define GL_SEPARATE_SPECULAR_COLOR_EXT		0x81FA

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT);
	//*/
}

void GLContext::flush() {
	glFinish();
	SwapBuffers(_window.hdc());
}
