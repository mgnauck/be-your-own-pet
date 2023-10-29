#include "SpermWorm.h"
#include "Intro.h"
#include "Scene.h"
#include "Shape.h"
#include "Mesh.h"
#include "Generator.h"
#include "GLContext.h"
#include "GLHelper.h"
#include <cmath>
#include "Map.h"

#include "../data/test1.h"
#include "../data/test2.h"
#include "../data/test3.h"

SpermWorm::SpermWorm(float stime) : Effect(stime), t(0.0f), update(0.0f), update2(0.0f), offset(0.0f) {

	int texs[3];

	// textures
	Map* map = load_from_h(test1, test1_width, test1_height);
	texs[0] = GLHelper().uploadTexture(*map, true);
	delete map;

	map = load_from_h(test2, test2_width, test2_height);
	texs[1] = GLHelper().uploadTexture(*map, true);
	delete map;

	map = load_from_h(test3, test3_width, test3_height);
	texs[2] = GLHelper().uploadTexture(*map, true);
	delete map;

#define SUBX			20
#define SUBY			50
#define POINT_COUNT		20

	Material m;

	// skybox
	m.ambient		= Vector(0.6f, 0.6f, 0.6f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.9f);
	m.specular		= Vector(0.0f, 0.0f, 0.0f);
	m.texture		= -1;
	m.shadowCasting	= false;

	Mesh* skybox = Generator(60, 60).makeSphere(50.0f, 1.0f, 1.0f, -1.0f);
	skybox->setMaterial(m);
	scene.add(skybox);

	// curves
	m.ambient		= Vector(0.2f, 0.2f, 0.2f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.specular		= Vector(1.0f, 1.0f, 1.0f);
	m.exponent		= 70.0f;
	m.shadowCasting	= true;

	for(int j=0; j<3; j++) {
		curves[j] = new Shape(SUBX, SUBY, 2.0f, 1.f);
		for(int i=0; i<POINT_COUNT; i++)
			curves[j]->addPoint(Vertex(Vector(rnd(-35.0f, 35.0f), rnd(-15.0f, 20.0f), rnd(-40.0f, 40.0f))));
		curves[j]->addPoint(curves[j]->getPoint(0)); // loop
		curves[j]->setShape(1.2f, 3.5f, 0.2276574f, 2.2f, true);
		curves[j]->setIntervall(0.0f, 0.05f);
		m.texture = texs[j];
		curves[j]->setMaterial(m);
		scene.add(curves[j]);
	}

	// planes
	m.texture		= renderTexture;
	m.illuminated	= false;
	m.backfaces		= true;

	int const count = 6;
	float rad = 40.0f;
	float s = 10.0f;
	for(int i=0; i<count; i++) {
		Mesh* plane = Generator(2, 2).makePlane(4.0f * s, 3.0f * s);
		float angle = (float)i / (float)count * 2.0f * PI;
		Matrix mat(true);
		mat.setCol3(3, Vector(sin(angle) * rad, 1.0f, cos(angle) * rad));
		mat *= Matrix().makeRotation(Vector(0.0f, 1.0f, 0.0f), angle);
		plane->setMatrix(mat);
		plane->setMaterial(m);
		scene.add(plane);
	}

	// scene stuff
	scene.setPlane(Plane(Vector(0.0f, 1.0f, 0.0f), 15.0f));
	scene.add(Light(Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 200.0f, 0.0f), 10, 10.0f));
}

void SpermWorm::run(float time) {

	if(time - update2 > 1000.0f) {

		offset += rnd(-1.0f, 1.0f) * 1000.0f;
		update2 = time;
	}

#define DIST 0.05f

	if(time - update > 40.0f) {

		if(t < (1.0f - DIST))
			t += 0.001f;
		else
			t = 0.0f;

		for(int i=0; i<3; i++)
			curves[i]->setIntervall(0.0f + t, DIST + t);

		update = time;
	}

	// set matrices
	Matrix view = Matrix().makeCamera(	Vector((float)sin(time * 0.0003) * 30.0f, (float)cos(time * 0.0006) * 11.0f + 5.0f, (float)cos(time * 0.0003) * 30.0f),
										Vector((float)cos(time * 0.0004) * 5.0f, (float)sin(time * 0.0003) * 5.0f, (float)sin(time * 0.0003) * 5.0f),
										Vector(0.0f, 1.0f, 0.0f));

	Matrix proj = Matrix().makePerspectiveProjection(60.0f, ASPECT, 1.0f, 1000.0f);

	scene.setProjection(proj);
	scene.setView(view);

	// render texture
	glh.clear();
	glh.setViewport(4, 25, RENDERTEXTURE_SIZEX - 8, RENDERTEXTURE_SIZEY - 50);
	glh.renderScene(time, scene, true);
	glh.copyToTexture(renderTexture, 0, 0, RENDERTEXTURE_SIZEX, RENDERTEXTURE_SIZEY);

	// fb texture
	/*
	glh.clear();
	glh.setViewport(0, 0, FRAMBUFFERTEXTURE_SIZEX, FRAMBUFFERTEXTURE_SIZEY);
	glh.renderScene(time, scene);
	glh.copyToTexture(framebufferTexture, 0, 0, FRAMBUFFERTEXTURE_SIZEX, FRAMBUFFERTEXTURE_SIZEY);

	// blit fb texture
	glh.clear();
	glh.setViewport(LEFT, BOTTOM, WIDTH, HEIGHT);
	glh.drawViewportQuad(framebufferTexture, 1.0f, 1.0f, Vector(1.0f, 1.0f, 1.0f));
	*/

	glh.clear();
	glh.setViewport(LEFT, BOTTOM, WIDTH, HEIGHT);
	glh.renderScene(time, scene);
}