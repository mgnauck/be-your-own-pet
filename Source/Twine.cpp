#include "Twine.h"
#include "Intro.h"
#include "Scene.h"
#include "Shape.h"
#include "Mesh.h"
#include "Generator.h"
#include "GLContext.h"
#include "GLHelper.h"
#include <cmath>
#include "Map.h"

Twine::Twine(float stime) : Effect(stime), update(0.0f), t(0.0f), actGrow(0) {

	// textures
	Map* map = new Map(64, 64, 0xff0000ff);
	int tex = GLHelper().uploadTexture(*map, true);
	delete map;

	Material m;

	m.ambient		= Vector(0.6f, 0.6f, 0.6f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.specular		= Vector(0.0f, 0.0f, 0.0f);
	m.texture		= -1;
	m.shadowCasting	= false;

	Mesh* skybox = Generator(20, 20).makeSphere(100.0f, 1.0f, 1.0f, -1.0f);
	skybox->setMaterial(m);
	scene.add(skybox);

	m.ambient		= Vector(0.1f, 0.1f, 0.1f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.specular		= Vector(1.0f, 1.0f, 1.0f);
	m.exponent		= 20.0f;
	m.texture		= tex;
	m.shadowCasting	= true;
	m.backfaces		= false;

	Vector	origin(0.0f, 24.0f, 0.0f);

	for(int j=0; j<SPLINE_COUNT; j++) {

		float pieceScale	= rnd(5.0f, 7.0f);
		shape[j]			= new Shape(10, 120, 1.0f, 1.0f);

		Vector actPos(origin);
		shape[j]->addPoint(Vertex(actPos));

		for(int i=0; i<PIECE_COUNT; i++) {
			actPos += Vector().rand() * pieceScale;
			shape[j]->addPoint(Vertex(actPos));
			pieceScale = rnd(6.0f, 13.0f);
		}
		
		shape[j]->setIntervall(0.0f, 0.0f);
		shape[j]->setShape(0.4f, 0.0f, 0.0f, 1.0f, true);
		shape[j]->setMaterial(m);
		scene.add(shape[j]);
	}

	scene.setPlane(Plane(Vector(0.0f, 1.0f, 0.0f), 15.0f));
	scene.add(Light(Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 400.0f, 0.0f), 10, 5.0f));
}

void Twine::run(float time) {

	if(time - update > 10.0f) {

		if(actGrow < SPLINE_COUNT - 2) {

			if(t < 1.0f) {
				t += (float)(time - update) * 0.000125f;
			} else {
				actGrow += 2;
				t = 0.0f;
			}

			shape[actGrow + 0]->setIntervall(0.0f, t);
			shape[actGrow + 1]->setIntervall(0.0f, t);
//			shape[actGrow + 2]->setIntervall(0.0f, t);
//			shape[actGrow + 3]->setIntervall(0.0f, t);
		}

		update = time;
	}

	// set matrices
	Matrix view = Matrix().makeCamera(	Vector((float)cos(time * 0.00021) * 33.0f, (float)cos(time * 0.0002) * 20.0f + 30.0f, (float)sin(time * 0.0002) * 30.0f),
										Vector((float)sin(time * 0.0001) * 20.0f, 10.0f * (float)sin(time * 0.0003) + 20.0f, (float)cos(time * 0.0002) * 20.0f),
										Vector(0.0f, 1.0f, 0.0f));

	Matrix proj = Matrix().makePerspectiveProjection(70.0f, ASPECT, 1.0f, 500.0f);

	scene.setProjection(proj);
	scene.setView(view);

	// blit fb texture
	glh.clear();
	glh.setViewport(LEFT, BOTTOM, WIDTH, HEIGHT);
	glh.renderScene(time, scene);
}