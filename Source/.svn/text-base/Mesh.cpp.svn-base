#include "Mesh.h"

Mesh::Mesh() : Renderable(), validRenderObject(false) {
}

Mesh::~Mesh() {
	clear(true);
}

void Mesh::add(Vertex const& v) {
	validRenderObject = false;
	vertices.push_back(v);
}

void Mesh::add(Triangle const& t) {
	validRenderObject = false;
	triangles.push_back(t);
}

void Mesh::triangulate(int subx, int suby) {
	for(int j=0; j<suby - 1; j++) {
		int row		= subx * j;
		int nextRow = subx * (j + 1);
		for(int i=0; i<subx - 1; i++) {
			add(Triangle(row + i, nextRow + i, nextRow + (i + 1)));
			add(Triangle(row + i, nextRow + (i + 1), row + (i + 1)));
		}
	}
}

void Mesh::calcNormals() {
	for(triangleList::iterator tit1=triangles.begin(); tit1!=triangles.end(); ++tit1)
		tit1->calcNormal(vertices[tit1->a].position, vertices[tit1->b].position, vertices[tit1->c].position);

	for(vertexList::iterator vit1=vertices.begin(); vit1!=vertices.end(); ++vit1)
		vit1->normal = Vector(0.0f, 0.0f, 0.0f);

	for(triangleList::iterator tit2=triangles.begin(); tit2!=triangles.end(); ++tit2) {
		vertices[tit2->a].normal += tit2->normal;
		vertices[tit2->b].normal += tit2->normal;
		vertices[tit2->c].normal += tit2->normal;
	}
	
	for(vertexList::iterator vit2=vertices.begin(); vit2!=vertices.end(); ++vit2)
		vit2->normal.normalize();
}

void Mesh::clear(bool clearTriangles) {
	vertices.clear();
	if(clearTriangles) {
		triangles.clear();
		renderTriangles.clear();
	}
}

void Mesh::prepareRender() {

	if(validRenderObject)
		return;

	// create render triangle array
	if(renderTriangles.empty()) {
		for(triangleList::iterator it=triangles.begin(); it!=triangles.end(); ++it) {
			RenderTriangle tri;
			tri.a = it->a;
			tri.b = it->b;
			tri.c = it->c;
			renderTriangles.push_back(tri);
		}
	}
}

vertexList& Mesh::getVertices() {
	return vertices;
}

triangleList& Mesh::getTriangles() {
	return triangles;
}

renderTriangleList& Mesh::getRenderTriangles() {
	return renderTriangles;
}

void Mesh::setInvalid() {
	validRenderObject = false;
}