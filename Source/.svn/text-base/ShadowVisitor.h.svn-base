#ifndef H_SHADOWVISITOR__
#define H_SHADOWVISITOR__

#include "RenderableVisitor.h"
#include "Matrix.h"

class Plane;

class ShadowVisitor : public RenderableVisitor {
public:
	ShadowVisitor(float t, Vector const& lpos, Plane const& p, Matrix const& v);
	void		visit(Renderable* r);

private:
	float		time;
	Matrix		proj;
	Matrix		view;
};

#endif