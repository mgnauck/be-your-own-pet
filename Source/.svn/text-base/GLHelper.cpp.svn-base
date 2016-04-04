#include "GLHelper.h"
#include "GLContext.h"
#include "Material.h"
#include "Map.h"
#include "Scene.h"
#include "RenderVisitor.h"
#include "ShadowVisitor.h"

//#define GL_BGRA_EXT 0x80E1

void GLHelper::setViewport(int l, int b, int w, int h) const {
	glViewport(l, b, w, h);
}

void GLHelper::clear(Vector const& c) const {
	glClearColor(c.x, c.y, c.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GLHelper::setLight(int n, Light const& l) const {
	glLightfv(GL_LIGHT0 + n, GL_POSITION, &l.position.x);
	glLightfv(GL_LIGHT0 + n, GL_AMBIENT, &(Vector(1.0f, 1.0f, 1.0f).x));
	glLightfv(GL_LIGHT0 + n, GL_DIFFUSE, &l.color.x);
	glLightfv(GL_LIGHT0 + n, GL_SPECULAR, &(Vector(1.0f, 1.0f, 1.0f).x));
	glEnable(GL_LIGHT0 + n);
}

void GLHelper::disableLights() const {
	for(int i=0; i<8; i++)
		glDisable(GL_LIGHT0 + i);
}

void GLHelper::setMaterial(Material const& m) const {
	glMaterialfv(GL_FRONT, GL_AMBIENT, &m.ambient.x);
	glMaterialfv(GL_FRONT, GL_EMISSION, &m.emissive.x);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, &m.diffuse.x);
	glMaterialfv(GL_FRONT, GL_SPECULAR, &m.specular.x);
	glMaterialf(GL_FRONT, GL_SHININESS, m.exponent);
}

void GLHelper::setMVP(Matrix const& mv, Matrix const& pr) const {
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&pr.transposed().m[0][0]);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(&mv.transposed().m[0][0]);
}

void GLHelper::bindTexture(int id) const {
	glBindTexture(GL_TEXTURE_2D, id);
}

int GLHelper::uploadTexture(Map const& m, bool mipmap, int minFilter, int magFilter) const {

	int w = m.getWidth();
	int h = m.getHeight();

	unsigned int id;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	if(!mipmap)
		glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, ((Map&)m).getPtr());
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, ((Map&)m).getPtr());
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	if(mipmap)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	else
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

	return id;
}

int GLHelper::createRenderTexture(int w, int h, int minFilter, int magFilter) const {
	Map m(w, h);
	return uploadTexture(m, false, minFilter, magFilter);
}

void GLHelper::copyToTexture(int texture, int l, int b, int w, int h) const {

	bindTexture(texture);
	glReadBuffer(GL_BACK);
	// target, mipmaplevel, xoffs in texture, yoffs, left of buffer, bottom, width, height
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, l, b, w, h); 
}

void GLHelper::drawViewportQuad(int id, float tx, float ty, Vector const& col) const {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDepthMask(0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glColor4fv(&col.x);
	if(id != -1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);
		glTexCoord2f(tx, 0.0f);
		glVertex2f(1.0f, -1.0f);
		glTexCoord2f(tx, ty);
		glVertex2f(1.0f, 1.0f);
		glTexCoord2f(0.0f, ty);
		glVertex2f(-1.0f, 1.0f);
	glEnd();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDepthMask(1);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void GLHelper::drawOvl(int id, float px, float py, float sx, float sy, float a) {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glScalef(sx, sy * 1.777f, 1.0f);		// 1.777 -> scal0r für aspect
	glTranslatef(px, py, 0.0f);

	glDepthMask(0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, id);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(0.0f, 0.0f, 0.0f, a);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-1.0f, -1.0f);
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDepthMask(1);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void GLHelper::blend(float alpha, Vector const& c) {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDepthMask(0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4f(c.x, c.y, c.z, alpha);

	glBegin(GL_QUADS);
		glVertex2f(-1.0f, 1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
		glVertex2f(-1.0f, -1.0f);
	glEnd();

	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(1);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void GLHelper::renderScene(float time, Scene& scene, bool low) const {

	// setup matrices
	setMVP(scene.getView(), scene.getProjection());

	// setup lights
	for(lightList::iterator it=scene.getLights().begin(); it!=scene.getLights().end(); ++it)
		setLight((int)std::distance(scene.getLights().begin(), it), *it);

	// render all objects
	scene.visit(&RenderVisitor(time));

	// setup shadows
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(false);
	glClearStencil(0x20);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_EQUAL, 0x20, 0xff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

	float doffs = 0.05f;

	// render shadows
	for(lightList::iterator lit=scene.getLights().begin(); lit!=scene.getLights().end(); ++lit) {

		float sampleCount = (float)lit->samples.size();

		if(low)
			sampleCount = 1;

		float t		= 0.2f / sampleCount;
		float offs	= -sampleCount * doffs * 0.5f;

		glColor4f(t, t, t, t);

		if(!low) {
			for(std::vector<Vector>::iterator sit=lit->samples.begin(); sit!=lit->samples.end(); ++sit) {

				glClear(GL_STENCIL_BUFFER_BIT);

				scene.visit(&ShadowVisitor(time, *sit, Plane(scene.getPlane().nrm, scene.getPlane().dist + offs), scene.getView()));
				offs += doffs;
			}

		} else {
			glClear(GL_STENCIL_BUFFER_BIT);
			scene.visit(&ShadowVisitor(time, lit->position, scene.getPlane(), scene.getView()));
		}
	}

	// cut the shit
	disableLights();
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_BLEND);
	glDepthMask(true);
}