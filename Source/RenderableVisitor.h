#ifndef H_RENDERABLEVISITOR__
#define H_RENDERABLEVISITOR__

class Renderable;

class RenderableVisitor {
public:
	virtual void visit(Renderable*) = 0;
};

#endif