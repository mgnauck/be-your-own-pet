#ifndef H_SHAPE__
#define H_SHAPE__

#include "Mesh.h"
#include "Spline.h"

class Shape : public Renderable {
public:
	Shape(int sx, int sy, float tx, float ty, bool b = false);
	virtual ~Shape();

	void						addPoint(Vertex const& v);
	void						setPoint(int n, Vector const& v);
	void						setShape(float s, float f, float m, float b, bool c, float cm = 0.1f);
	void						setIntervall(float b0, float b1);
	void						tesselate();

	Vertex const&				getPoint(int n) const;
	int							getPointCount() const;
	void						prepareRender();

	vertexList&					getVertices();
	virtual renderTriangleList&	getRenderTriangles();

private:
	int							subx;
	int							suby;
	float						texx;
	float						texy;
	float						t0;
	float						t1;

	float						scale;		// shape
	float						freq;
	float						multiply;
	float						bias;
	bool						closed;
	float						closeMul;
	bool						band;

	Spline						spline;
	Mesh						mesh;
	bool						validRenderObject;
	bool						hasTriangles;
};

#endif