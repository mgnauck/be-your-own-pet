#include "RenderVisitor.h"
#include "Renderable.h"
#include "GLContext.h"
#include "GLHelper.h"

RenderVisitor::RenderVisitor(float t) {
	time = t;
}

void RenderVisitor::visit(Renderable* r) {

	Material mat = r->getMaterial();

	if(mat.illuminated) {
		GLHelper().setMaterial(mat);
		glEnable(GL_LIGHTING);
	} else
		glColor3fv(&mat.diffuse.x);

	if(mat.texture != -1) {
		GLHelper().bindTexture(mat.texture);
		glEnable(GL_TEXTURE_2D);
	}

	if(mat.backfaces)
		glDisable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	if(mat.illuminated)
		glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(&r->getMatrix().transposed().m[0][0]);

	r->prepareRender();

	vertexList& verts = r->getVertices();
	renderTriangleList& tris = r->getRenderTriangles();

	int stride = (int)(((char*)&verts[1]) - ((char*)&verts[0]));

	glVertexPointer(4, GL_FLOAT, stride, &verts[0].position.x);
	if(mat.illuminated)
		glNormalPointer(GL_FLOAT, stride, &verts[0].normal.x);
	glTexCoordPointer(2, GL_FLOAT, stride, &verts[0].texel.x);
	glDrawElements(GL_TRIANGLES, (int)tris.size() * 3, GL_UNSIGNED_INT, &tris[0].a);

	glPopMatrix();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}