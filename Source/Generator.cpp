#include "Generator.h"
#include <cmath>

Generator::Generator(int sx, int sy) : subx(sx), suby(sy) {}

Mesh* Generator::makePlane(float scalex, float scaley, float texx, float texy) const {
	Mesh*	mesh = new Mesh();
	float	dx	= 1.0f / (float)(subx - 1);
	float	dy	= 1.0f / (float)(suby - 1);
	float	y	= 0.5f;

	for(int j=0; j<suby; j++) {
		float x = -0.5f;
		for(int i=0; i<subx; i++) {
			Vertex v;
			v.position = Vector(x * scalex, y * scaley, 0.0f);
			v.normal = Vector(0.0f, 0.0f, 1.0f);
			v.texel	= Vector(texx * (x + 0.5f), texy * (y + 0.5f), 0.0f);
			mesh->add(v);
			x += dx;
		}
		y -= dy;
	}

	mesh->triangulate(subx, suby);
	//mesh->calcNormals();

	return mesh;
}

Mesh* Generator::makeSphere(float radius, float texx, float texy, float dir) const {
	Mesh*	mesh = new Mesh();
	float	dradius	= PI / (float)(suby - 1);
	float	dalpha	= 2.0f * PI / (float)(subx - 1);
	float	r		= 0.0f;
	float	dtx		= 1.0f / (float)(subx - 1);
	float	dty		= 1.0f / (float)(suby - 1);
	float	ty		= 0.0f;

	for(int j=0; j<suby; j++) {
		float a = 0.0f;
		float tx = 0.0f;
		for(int i=0; i<subx; i++) {
			Vertex v;
			float rad = radius * (float)sin(r);
			v.position = dir * Vector(rad * cos(a), rad * sin(a), radius * cos(r));
			v.normal = dir * v.position.normalized();
			v.texel	= Vector(tx * texx, ty * texy, 0.0f);
			mesh->add(v);
			a += dalpha;
			tx += dtx;
		}
		r += dradius;
		ty += dty;
	}

	mesh->triangulate(subx, suby);
	//mesh->calcNormals();

	return mesh;
}

Mesh* Generator::makeBox(float scalex, float scaley, float scalez, float texx, float texy) const {
	return new Mesh();
}