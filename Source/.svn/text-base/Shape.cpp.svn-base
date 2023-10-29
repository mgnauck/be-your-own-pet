#include "Shape.h"
#include <cmath>

Shape::Shape(int sx, int sy, float tx, float ty, bool b) : Renderable(), spline(3), validRenderObject(false), hasTriangles(false), band(b) {
	subx	= sx;
	suby	= sy;
	texx	= tx;
	texy	= ty;
	t0		= 0.0f;		// intervall
	t1		= 1.0f;
	setShape(1.0f, 1.0f, 0.0f, 1.0f, false);
}

Shape::~Shape() {
}

void Shape::addPoint(Vertex const& v) {
	spline.addPoint(v);
	validRenderObject = false;
}

void Shape::setPoint(int n, Vector const& v) {
	spline.setPoint(n, v);
	validRenderObject = false;
}

void Shape::setShape(float s, float f, float m, float b, bool c, float cm) {
	scale		= s;
	freq		= f;
	multiply	= m;
	bias		= b;
	closed		= c;
	closeMul	= cm;
	validRenderObject = false;
}

void Shape::setIntervall(float b0, float b1) {
	t0 = b0;
	t1 = b1;
	validRenderObject = false;
}

void Shape::tesselate() {

	if(t0 == t1 || t1 == 0.0f)
		return;

	// del exisiting vertex & face infos
	mesh.clear(false);

	// tesselate Shape
	bool	calcNorms	= false;
	float	ist			= spline.getIntervallStart();
	float	len			= spline.getIntervallEnd() - ist;
	float	t0l			= t0 * len;
	float	dx			= 1.0f / (float)(subx - 1);
	float	dy			= (t1 * len - t0l) / (float)(suby - 1);
	float	y			= ist + t0l;
	float	dty			= 1.0f / (float)(suby - 1);
	float	ty			= 0.0f;

	for(int j=0; j<suby; j++) {		// suby - 1 for special treatment

		Vertex	v0	= spline.eval(y);
		Vertex	v1	= spline.eval(y + dy);
		float	x	= 0.0f;

		// fake frenet
		Vector	t	= v1.position - v0.position;
		Vector	n	= v1.position + v0.position;
		Vector	b	= t.cross(n);

		n = b.cross(t);
		n.normalize();
		b.normalize();

		float wave = (float)(sin(((float)j / (float)suby) * 2.0f * PI * freq) + 1.0) * multiply + bias;
		for(int i=0; i<subx; i++) {

			float a = -x * 2.0f * PI;

			float close = 1.0f;

			if(closed) {		// derb hack!
				if(j < 11)
					close = (float)j * closeMul;
				else if(j > suby - 11)
					close = (float)(suby - j - 1) * closeMul;
			}

			Vertex o;
			if(!band) {

				o.normal	= (sin(a) * b + cos(a) * n);
				o.position	= v0.position + o.normal * scale * wave * close;
				o.texel		= Vector(texx * x, texy * ty, 0.0f);

			} else {

				o.position	= v0.position + b * 10.0f * (x - 0.5f);
				o.texel		= Vector(texx * x, texy * ty, 0.0f);
			}

			mesh.add(o);
			x += dx;
		}
		y += dy;
		ty += dty;
	}

	if(!hasTriangles) {
		mesh.triangulate(subx, suby);
		hasTriangles = true;
	}

	if(band)
		mesh.calcNormals();
}

Vertex const& Shape::getPoint(int n) const {
	return spline.getPoint(n);
}

int Shape::getPointCount() const {
	return spline.getCount();
}

void Shape::prepareRender() {
	if(!validRenderObject) {
		tesselate();
		mesh.prepareRender();
		validRenderObject = true;
	}
}

vertexList&	Shape::getVertices() {
	return mesh.getVertices();
}

renderTriangleList& Shape::getRenderTriangles() {
	return mesh.getRenderTriangles();
}