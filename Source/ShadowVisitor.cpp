#include "ShadowVisitor.h"
#include "Renderable.h"
#include "GLContext.h"
#include "GLHelper.h"
#include "Plane.h"

ShadowVisitor::ShadowVisitor(float t, Vector const& lpos, Plane const& p, Matrix const& v) : time(t), view(v) {

	float nl	= p.nrm.dot(lpos);
	float nld	= nl + p.dist;

	proj.setRow3(0, Vector(nld - lpos.x * p.nrm.x, -lpos.x * p.nrm.y, -lpos.x * p.nrm.z));
	proj.setRow3(1, Vector(-lpos.y * p.nrm.x, nld - lpos.y * p.nrm.y, -lpos.y * p.nrm.z));
	proj.setRow3(2, Vector(-lpos.z * p.nrm.x, -lpos.z * p.nrm.y, nld - lpos.z * p.nrm.z));
	proj.setRow3(3, Vector(-p.nrm.x, -p.nrm.y, -p.nrm.z));
	proj.setCol3(3, Vector(-lpos.x * p.dist, -lpos.y * p.dist, -lpos.z * p.dist));
	proj.m[3][3] = nl;
}

void ShadowVisitor::visit(Renderable* r) {

	if(!r->getMaterial().shadowCasting)
		return;

	/*
		we would do:

		v' = (proj) * (view * shadow * model) * v
			   ^^           ^^
		     GL_PROJ    GL_MODELVIEW

		but because the fog depends on the modelview matrix (which we fuck this way
		due to shadow projection) we need:

		v' = (proj * shadow') * (view * model) * v

		where

		shadow' * view = view * shadow

		->

		shadow' = view * shadow * view^-1

	*/
	
	Matrix projTmp = view * proj * view.inverted();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMultMatrixf(&projTmp.transposed().m[0][0]);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(&r->getMatrix().transposed().m[0][0]);

	glEnableClientState(GL_VERTEX_ARRAY);

	r->prepareRender();

	vertexList& verts = r->getVertices();
	renderTriangleList& tris = r->getRenderTriangles();

	int stride = (int)(((char*)&verts[1]) - ((char*)&verts[0]));

	glVertexPointer(4, GL_FLOAT, stride, &verts[0].position.x);
	glDrawElements(GL_TRIANGLES, (int)tris.size() * 3, GL_UNSIGNED_INT, &tris[0].a);

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}