#include "FFDObject.h"
#include <iterator>

FFDObject::FFDObject(Mesh* m) : originalMesh(m), valid(false), points(64), bu(4), bv(4), bw(4			) {

	findBounds();
	setupRestStatePoints();
	transformToLatticeSpace();
	
	// copy verts+tris from original to deformed mesh
	for(vertexList::iterator vit=originalMesh->getVertices().begin(); vit!=originalMesh->getVertices().end(); ++vit)
		deformedMesh.add(*vit);
	for(triangleList::iterator tit=originalMesh->getTriangles().begin(); tit!=originalMesh->getTriangles().end(); ++tit)
		deformedMesh.add(*tit);
}

FFDObject::~FFDObject() {

	points.clear();
	restStatePoints.clear();
	latticeSpacePoints.clear();
	delete originalMesh;
	bu.clear();
	bv.clear();
	bw.clear();
}

void FFDObject::setPoint(int n, Vector const& v) {
	points[n] = v;
	valid = false;
}

Vector const& FFDObject::getPoint(int n) {
	return points[n];
}

void FFDObject::findBounds() {

	// find min and max coords per axis
	vertexList::iterator it=originalMesh->getVertices().begin();

	max = Vector(it->position);
	min = Vector(it->position);

	for(; it!=originalMesh->getVertices().end(); ++it) {
		Vector act(it->position);
		min.x = (min.x > act.x) ? act.x : min.x;
		min.y = (min.y > act.y) ? act.y : min.y;
		min.z = (min.z > act.z) ? act.z : min.z;
		max.x = (max.x < act.x) ? act.x : max.x;
		max.y = (max.y < act.y) ? act.y : max.y;
		max.z = (max.z < act.z) ? act.z : max.z;
	}
}

void FFDObject::setupRestStatePoints() {

	// basierend auf dims control points setzen
	Vector d(max - min);

	for(int k=0; k<4; k++)
		for(int j=0; j<4; j++)
			for(int i=0; i<4; i++)
				restStatePoints.push_back(Vector(min.x + (d.x * (float)i / 3.0f), min.y + (d.y * (float)j / 3.0f), min.z + (d.z * (float)k / 3.0f)));
}

void FFDObject::resetPoints() {
	for(vectorList::iterator it=restStatePoints.begin(); it!=restStatePoints.end(); ++it)
		points[std::distance(restStatePoints.begin(), it)] = *it;
}

void FFDObject::transformToLatticeSpace() {

	latticeSpacePoints.clear();
	Vector dim(max - min);

	// transform all verts of original mesh to lattice space
	for(vertexList::iterator it=originalMesh->getVertices().begin(); it!=originalMesh->getVertices().end(); ++it) {

		Vector act(it->position);

		act -= min;			// bias + scale verts to [0..1]
		act.x /= dim.x;
		act.y /= dim.y;
		act.z /= dim.z;

		/*
		assert((act.x >= 0.0f) && (act.x <= 1.0f));
		assert((act.y >= 0.0f) && (act.y <= 1.0f));
		assert((act.z >= 0.0f) && (act.z <= 1.0f));
		*/

		latticeSpacePoints.push_back(act);
	}
}

void FFDObject::transformToObjectSpace() {

	// do the deformation (based on controlpoints) for every point in lattice space
	std::vector<Vertex>& verts = deformedMesh.getVertices();
	for(std::vector<Vector>::iterator it=latticeSpacePoints.begin(); it!=latticeSpacePoints.end(); ++it)
		verts[std::distance(latticeSpacePoints.begin(), it)].position = evalPoint(it->x, it->y, it->z);
}

Vector FFDObject::evalPoint(float u, float v, float w) {

	// bernstein polynomials (degree 3)

	float u2	= u * u;
	float u1	= 1.0f - u;
	float u12	= u1 * u1;

	bu[0] = u1 * u12;
	bu[1] = 3.0f * u * u12;
	bu[2] = 3.0f * u2 * u1;
	bu[3] = u * u2;

	float v2	= v * v;
	float v1	= 1.0f - v;
	float v12	= v1 * v1;

	bv[0] = v1 * v12;
	bv[1] = 3.0f * v * v12;
	bv[2] = 3.0f * v2 * v1;
	bv[3] = v * v2;

	float w2	= w * w;
	float w1	= 1.0f - w;
	float w12	= w1 * w1;

	bw[0] = w1 * w12;
	bw[1] = 3.0f * w * w12;
	bw[2] = 3.0f * w2 * w1;
	bw[3] = w * w2;

	Vector p(0.0f, 0.0f, 0.0f);

	// sum influences based on bernstein polynomials and control points
	for(int k=0; k<4; k++)
		for(int j=0; j<4; j++)
			for(int i=0; i<4; i++)
				p += points[(k << 4) + (j << 2) + i] * bu[i] * bv[j] * bw[k];

	return p;
}

void FFDObject::prepareRender() {

	if(!valid) {
		transformToObjectSpace();
		deformedMesh.calcNormals();
		deformedMesh.setInvalid();
		deformedMesh.prepareRender();
		valid = true;
	}
}

vertexList&	FFDObject::getVertices() {
	return deformedMesh.getVertices();
}

renderTriangleList& FFDObject::getRenderTriangles() {
	return deformedMesh.getRenderTriangles();
}
