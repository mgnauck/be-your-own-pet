#ifndef H_GENERATOR__
#define H_GENERATOR__

#include "Mesh.h"

class Generator {
public:
	Generator(int sx, int sy);

	Mesh* makePlane(float scalex, float scaley, float texx = 1.0f, float texy = 1.0f) const;
	Mesh* makeSphere(float r, float texx = 1.0f, float texy = 1.0f, float dir = 1.0f) const;
	Mesh* makeBox(float scalex, float scaley, float scalez, float texx = 1.0f, float texy = 1.0f) const;

private:
	int subx;
	int suby;
};

#endif