#include "Scene.h"
#include "RenderableVisitor.h"
#include "Renderable.h"

Scene::Scene(): plane(Vector(0.0f, 1.0f, 0.0f), 0.0f) {
	view.makeIdentity();
	projection.makeIdentity();
}

Scene::~Scene() {
	for(renderableList::iterator it=renderables.begin(); it!=renderables.end(); ++it)
		delete *it;
	renderables.clear();
	lights.clear();
}

void Scene::add(Renderable* r){
	r->prepareRender();
	renderables.push_back(r);
}

void Scene::add(Light const& l){
	lights.push_back(l);
}

lightList& Scene::getLights() {
	return lights;
}

void Scene::visit(RenderableVisitor* v) {
	// visit all renderables
	for(renderableList::iterator it=renderables.begin(); it!=renderables.end(); ++it)
		v->visit(*it);
}

void Scene::setView(Matrix const& v) {
	view = v;
}

void Scene::setProjection(Matrix const& p) {
	projection = p;
}

Matrix const& Scene::getView() const {
	return view;
}

Matrix const& Scene::getProjection() const {
	return projection;
}

void Scene::setPlane(Plane const& p) {
	plane = p;
}

Plane const& Scene::getPlane() const {
	return plane;
}