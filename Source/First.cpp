#include "First.h"
#include "Intro.h"
#include "Scene.h"
#include "Mesh.h"
#include "Generator.h"
#include "GLContext.h"
#include "GLHelper.h"
#include <cmath>

First::First(float stime) : Effect(stime) {

	Material m;

	m.ambient		= Vector(0.6f, 0.6f, 0.6f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.specular		= Vector(0.0f, 0.0f, 0.0f);
	m.texture		= -1;
	m.shadowCasting	= false;

	Mesh* skybox = Generator(20, 20).makeSphere(100.0f, 1.0f, 1.0f, -1.0f);
	skybox->setMaterial(m);
	scene.add(skybox);

	scene.setPlane(Plane(Vector(0.0f, 1.0f, 0.0f), 15.0f));
	scene.add(Light(Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 400.0f, 0.0f), 10, 4.0f));
}

void First::run(float time) {

	// set matrices
	Matrix view = Matrix().makeCamera(	Vector(33.0f, 50.0f, 0.0f),
										Vector(0.0f, 20.0f, 20.0f),
										Vector(0.0f, 1.0f, 0.0f));

	Matrix proj = Matrix().makePerspectiveProjection(70.0f, ASPECT, 1.0f, 500.0f);

	scene.setProjection(proj);
	scene.setView(view);

	// blit fb texture
	glh.clear();
	glh.setViewport(LEFT, BOTTOM, WIDTH, HEIGHT);
	glh.renderScene(time, scene);
}