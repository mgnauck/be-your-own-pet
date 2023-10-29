#ifndef H_SCENE__
#define H_SCENE__

#include <vector>
#include "Light.h"
#include "Plane.h"
#include "Matrix.h"

class Renderable;
class RenderableVisitor;

class Scene {
public:
	Scene();
	~Scene();
	
	void							add(Renderable* r);
	void							add(Light const& l);
	std::vector<Light>&				getLights();
	void							visit(RenderableVisitor* v);

	void							setView(Matrix const& v);
	void							setProjection(Matrix const& p);
	Matrix const&					getView() const;
	Matrix const&					getProjection() const;

	void							setPlane(Plane const& p);
	Plane const&					getPlane() const;

private:
	std::vector<Renderable*>		renderables;
	std::vector<Light>				lights;
	Plane							plane;

	Matrix							view;
	Matrix							projection;
};

typedef std::vector<Renderable*>	renderableList;
typedef std::vector<Light>			lightList;

#endif