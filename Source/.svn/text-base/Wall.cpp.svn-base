#include "Wall.h"
#include "Intro.h"
#include "Scene.h"
#include "Shape.h"
#include "Mesh.h"
#include "Generator.h"
#include "GLContext.h"
#include "GLHelper.h"
#include <cmath>
#include "Map.h"

#include "../data/test6.h"
#include "../data/gfx.h"
#include "../data/music.h"
#include "../data/code.h"

Wall::Wall(float stime) : Effect(stime), update(0.0f), switchNoise(0), ovlSwitch(0) {

	Map* map = load_from_h(test6, test6_width, test6_height);
	texs[0] = GLHelper().uploadTexture(*map, true);
	delete map;

	map = noiseMap(64, 64);
	texs[1] = GLHelper().uploadTexture(*map, false);
	delete map;

	map = noiseMap(64, 64);
	texs[2] = GLHelper().uploadTexture(*map, false);
	delete map;

	map = noiseMap(64, 64);
	texs[3] = GLHelper().uploadTexture(*map, false);
	delete map;

	map = load_from_h(gfx, gfx_width, gfx_height, true);
	texs[4] = GLHelper().uploadTexture(*map, true);
	delete map;

	map = load_from_h(music, music_width, music_height, true);
	texs[5] = GLHelper().uploadTexture(*map, true);
	delete map;

	map = load_from_h(code, code_width, code_height, true);
	texs[6] = GLHelper().uploadTexture(*map, true);
	delete map;

	Material m;

	m.ambient		= Vector(0.6f, 0.6f, 0.6f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.texture		= -1;
	m.shadowCasting	= false;

	Mesh* skybox = Generator(60, 60).makeSphere(100.0f, 1.0f, 1.0f, -1.0f);
	skybox->setMaterial(m);
	scene.add(skybox);

	// monis
	m.ambient		= Vector(0.2f, 0.2f, 0.2f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.texture		= renderTexture;
	m.shadowCasting	= true;
	m.backfaces		= true;
	m.illuminated	= false;

	float sx = 50.0f;
	float sy = 50.0f;
	float tx = 1.0f;
	float ty = 1.0f;
	float px = sx / 2.0f;

	Mesh* plane1 = Generator(2, 2).makePlane(sx, sy, tx, ty);
	Matrix mat(true);
	mat.setCol3(3, Vector(0.0f, 0.0f, px));
	plane1->setMaterial(m);
	plane1->setMatrix(mat);
	scene.add(plane1);

	Mesh* plane2 = Generator(2, 2).makePlane(sx, sy, tx, ty);
	Matrix mat2(true);
	mat2.setCol3(3, Vector(0.0f, 0.0f, -px));
	mat2 *= Matrix().makeRotation(Vector(0.0f, 1.0f, 0.0f), PI);
	plane2->setMaterial(m);
	plane2->setMatrix(mat2);
	scene.add(plane2);

	Mesh* plane3 = Generator(2, 2).makePlane(sx, sy, tx, ty);
	Matrix mat3(true);
	mat3.setCol3(3, Vector(-px, 0.0f, 0.0f));
	mat3 *= Matrix().makeRotation(Vector(0.0f, 1.0f, 0.0f), 2.0f * PI - PI * 0.5f);
	plane3->setMaterial(m);
	plane3->setMatrix(mat3);
	scene.add(plane3);

	Mesh* plane4 = Generator(2, 2).makePlane(sx, sy, tx, ty);
	Matrix mat4(true);
	mat4.setCol3(3, Vector(px, 0.0f, 0.0f));
	mat4 *= Matrix().makeRotation(Vector(0.0f, 1.0f, 0.0f), PI * 0.5f);
	plane4->setMaterial(m);
	plane4->setMatrix(mat4);
	scene.add(plane4);

	// spline maen
	m.ambient		= Vector(0.2f, 0.2f, 0.2f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.specular		= Vector(1.0f, 1.0f, 1.0f);
	m.exponent		= 80.0f;
	m.texture		= texs[0];
	m.shadowCasting	= true;
	m.backfaces		= true;
	m.illuminated	= true;

	int		sub		= 36;
	float	dt		= 2.0f * PI / (float)(sub - 1);
	float	r		= 48.0f;
	float	t		= 0.0f;
	
	shape			= new Shape(10, 400, 1.0f, 10.0f);

	shape->addPoint(Vertex(Vector(0.0f, 0.0f, 1.0f * r)));
	for(int i=1; i<sub; i++) {
		shape->addPoint(Vertex(Vector(sin(t) * r + rnd(0.0f, 7.0f), rnd(-9.0f, 9.0f), cos(t) * r + rnd(0.0f, 7.0f))));
		t += dt;
	}

	Matrix mat5(true);
	mat5.setCol3(3, Vector(0.0f, -5.0f, 0.0f));
	shape->setMatrix(mat5);
	shape->addPoint(Vertex(Vector(0.0f, 0.0f, 1.0f * r)));
	shape->setShape(1.0f, 3.0f, 0.8f, 0.8f, false);
	shape->setMaterial(m);
	scene.add(shape);

	scene.setPlane(Plane(Vector(0.0f, 1.0f, 0.0f), 25.2f));
	scene.add(Light(Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 200.0f, 0.0f), 10, 10.0f));
}

void Wall::run(float time) {

	if(time - update > 4000.0f) {
		ovlSwitch++;
		update = time;
	}

	switchNoise++;

	float r = 53.0f;
	Matrix view = Matrix().makeCamera(	Vector(r * cos(time * 0.0003f) + 1.5f * sin(time * 0.0004), -18.0f, r * sin(time * 0.0003f) + 1.5f * sin(time * 0.0004)),
										Vector(0.0f, 0.0f, 0.0f),
										Vector(0.0f, 1.0f, 0.0f));

	Matrix proj = Matrix().makePerspectiveProjection(80.0f, ASPECT, 1.0f, 1000.0f);

	scene.setProjection(proj);
	scene.setView(view);

	glh.clear();
	glh.setViewport(7, 7, RENDERTEXTURE_SIZEX - 14, RENDERTEXTURE_SIZEY - 14);
	glh.renderScene(time, scene, false);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
	Vector c(1.0f, 1.0f, 1.0f);
	c.w = 0.6f + (0.3f + 0.3f * (float)sin(time * 0.001));
	glh.drawViewportQuad(texs[1 + (switchNoise % 3)], (2.0f + c.w) * 1.333f, (2.0f + c.w), c);
	glDisable(GL_BLEND);
	glh.blend(0.6f, Vector(1.0f, 1.0f, 1.0f));
	glh.drawOvl(texs[4 + (ovlSwitch % 3)], 0.0f, 0.0f, 1.0f, 1.0f * 9.0f / 20.0f, 1.0f);
	glh.copyToTexture(renderTexture, 0, 0, RENDERTEXTURE_SIZEX, RENDERTEXTURE_SIZEY);

	glh.clear();
	glh.setViewport(LEFT, BOTTOM, WIDTH, HEIGHT);
	glh.renderScene(time, scene);
}