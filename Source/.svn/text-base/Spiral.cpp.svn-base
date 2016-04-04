#include "Spiral.h"
#include "Intro.h"
#include "Scene.h"
#include "Shape.h"
#include "Mesh.h"
#include "Generator.h"
#include "GLContext.h"
#include "GLHelper.h"
#include <cmath>
#include "Map.h"
#include "Spline.h"

#include "../data/test4.h"
#include "../data/test5.h"

Spiral::Spiral(float stime) : Effect(stime) {

	int texs[2];

	// textures
	Map* map = load_from_h(test4, test4_width, test4_height);
	texs[0] = GLHelper().uploadTexture(*map, true);
	delete map;

	map = load_from_h(test5, test5_width, test5_height);
	texs[1] = GLHelper().uploadTexture(*map, true);
	delete map;

	Material m;

	m.ambient		= Vector(0.6f, 0.6f, 0.6f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.specular		= Vector(0.0f, 0.0f, 0.0f);
	m.texture		= -1;
	m.shadowCasting	= false;

	Mesh* skybox = Generator(60, 60).makeSphere(250.0f, 1.0f, 1.0f, -1.0f);
	skybox->setMaterial(m);
	scene.add(skybox);
	
	m.ambient		= Vector(0.2f, 0.2f, 0.2f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.specular		= Vector(1.0f, 1.0f, 1.0f);
	m.exponent		= 90.0f;
	m.shadowCasting	= true;

	for(int j=0; j<2; j++) {

		// weg spline
		int		count	= 40;
		float	sx		= 10.0f;
		Spline* spline	= new Spline(3);

		for(int i=0; i<count; i++)
			if(j==0)
				spline->addPoint(Vertex(Vector((float)(i - (count / 2)) * sx, rnd(-10.0f, 30.0f), rnd(-80.0f, 80.0f))));
			else
				spline->addPoint(Vertex(Vector(rnd(-80.0f, 80.0f), rnd(-10.0f, 30.0f), (float)(i - (count / 2)) * sx)));

		// make spline shape
		Vector	up(0.0f, 1.0f, 0.0f);
		float	rad		= 20.0f;
		int		sub		= 80;
		float	dt		= (spline->getIntervallEnd() - spline->getIntervallStart()) / (float)sub;
		float	t		= 0.0f;
		float	x		= 0.0f;
		float	dx		= 2.0f * PI / (float)sub;
		Shape*	shape	= new Shape(15, 800, 1.0f, 5.0f);
		float	periode	= 315.0f;

		for(int i=0; i<sub; i++) {

			Vector p(spline->eval(t).position);
			Vector fw(spline->eval(t + dt).position - p);
			fw.normalize();
			Vector ri(fw.cross(up));
			ri.normalize();

			shape->addPoint(Vertex(Vector(p + (float)sin(t * periode) * rad * up + (float)cos(t * periode) * rad * ri)));

			t += dt;
			x += dx;
		}

		shape->setShape(0.4f, 20.0f, 1.5f, 2.0f, false);
		m.texture = texs[j];
		shape->setMaterial(m);
		scene.add(shape);
	}

	// scene stuff
	scene.setPlane(Plane(Vector(0.0f, 1.0f, 0.0f), 20.0f));
	scene.add(Light(Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 3000.0f, 0.0f), 10, 150.0f));
}

void Spiral::run(float time) {

	// set matrices
	Matrix view = Matrix().makeCamera(	Vector((float)cos(time * 0.0001) * 90.0f, (float)cos(time * 0.0003) * 45.0f + 40.0f, (float)sin(time * 0.0001) * 60.0f),
										Vector((float)sin(time * 0.0003) * 80.0f, (float)sin(time * 0.0003) * 15.0f + 10.0f, (float)cos(time * 0.0003) * 50.0f),
										Vector(0.0f, 0.8f + (float)cos(time * 0.00001) * 0.2f, (float)sin(time * 0.00001) * 0.2f + 0.2f));

	Matrix proj = Matrix().makePerspectiveProjection(90.0f, ASPECT, 1.0f, 1000.0f);

	scene.setProjection(proj);
	scene.setView(view);

	glh.clear();
	glh.setViewport(LEFT, BOTTOM, WIDTH, HEIGHT);
	glh.renderScene(time, scene);
}