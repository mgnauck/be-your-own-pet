#ifndef H_RENDERVISITOR__
#define H_RENDERVISITOR__

#include "RenderableVisitor.h"

class RenderObject;

class RenderVisitor : public RenderableVisitor {
public:
	RenderVisitor(float t);
	virtual ~RenderVisitor() {}

	virtual void	visit(Renderable* r);

protected:
	float			time;
};

#endif