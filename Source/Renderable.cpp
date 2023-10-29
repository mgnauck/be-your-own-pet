#include "Renderable.h"

Renderable::Renderable() : transformation(Matrix().identity()) {}

Renderable::~Renderable() {}

void Renderable::setMatrix(Matrix const& m) {
	transformation = m;
}

void Renderable::setMaterial(Material const& m) {
	material = m;
}

Matrix& Renderable::getMatrix() {
	return transformation;
}

Material& Renderable::getMaterial() {
	return material;
}