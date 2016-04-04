#include "Deformator.h"
#include "Intro.h"
#include "Scene.h"
#include "FFDObject.h"
#include "Mesh.h"
#include "Generator.h"
#include "GLContext.h"
#include "GLHelper.h"
#include "Map.h"
#include <cmath>

#include "../data/test4.h"

Deformator::Deformator(float stime) : Effect(stime), switchNoise(0) {

	on = false;
	update = 0.0f;

	// textures
	Map* map = load_from_h(test4, test4_width, test4_height);
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

	Material m;

	m.ambient		= Vector(0.6f, 0.6f, 0.6f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.specular		= Vector(0.0f, 0.0f, 0.0f);
	m.texture		= -1;
	m.shadowCasting	= false;

	Mesh* skybox = Generator(60, 60).makeSphere(70.0f, 1.0f, 1.0f, -1.0f);
	skybox->setMaterial(m);
	scene.add(skybox);

	m.ambient		= Vector(0.2f, 0.2f, 0.2f);
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.specular		= Vector(1.0f, 1.0f, 1.0f);
	m.exponent		= 70.0f;
	m.texture		= texs[0];
	m.shadowCasting	= true;

	Mesh* sphere = Generator(50, 50).makeSphere(6.0f, 1.0f, 6.5f);
	ffdObj = new FFDObject(sphere);
	ffdObj->setMaterial(m);
	scene.add(ffdObj);

	m.texture		= renderTexture;
	m.diffuse		= Vector(0.8f, 0.8f, 0.8f);
	m.illuminated	= false;
	m.backfaces		= true;

	// planes
	Vector	o(0.0f, -12.0f, 5.0f);
	float	sx	= 12.0f;		// sizex
	float	sy	= 9.0f;			// sizey
	float   mx	= 0.8f;
	float   my	= 1.3f;
	float   mz	= 0.8f;
	float	x	= 14.0f;
	int		k	= 0;

	for(int cnt=3; cnt>0; cnt--) {

		float y = 0.0f;
		for(int i=0; i<cnt; i++) {

			Matrix mat(true);
			mat.setCol3(3, o + Vector(-x * mx, y * my, x * mz));
			mat *= Matrix().makeRotation(Vector(0.0f, 1.0f, 0.0f), PI * 0.25f);

			planeLe[k] = Generator(2, 2).makePlane(sx, sy, 1.0f, 1.0f);
			planeLe[k]->setMatrix(mat);
			planeLe[k]->setMaterial(m);
			scene.add(planeLe[k]);

			mat.makeIdentity();
			mat.setCol3(3, o + Vector(x * mx, y * my, x * mz));
			mat *= Matrix().makeRotation(Vector(0.0f, 1.0f, 0.0f), 1.75f * PI);

			planeRi[k] = Generator(2, 2).makePlane(sx, sy, 1.0f, 1.0f);
			planeRi[k]->setMatrix(mat);
			planeRi[k]->setMaterial(m);
			scene.add(planeRi[k]);

			y += sy;
			k++;
		}
		x += sx;
	}

	scene.setPlane(Plane(Vector(0.0f, 1.0f, 0.0f), 16.0f));
	scene.add(Light(Vector(1.0f, 1.0f, 1.0f), Vector(0.0f, 200.0f, -200.0f), 10, 4.0f));
}

void Deformator::run(float time) {

	// deformation
	ffdObj->resetPoints();

	// set matrix of wobble dings
	Matrix mat(true);
	mat.setCol3(3, Vector(0.0f, sin(time * 0.0006) * 2.0f - 2.0f, 30.0f));
	mat *= Matrix().makeRotation(Vector(0.0f, 1.0f, 0.0f), time * 0.0004f);
	mat *= Matrix().makeRotation(Vector(0.0f, 0.0f, 1.0f), time * 0.0006f);
	ffdObj->setMatrix(mat);

	float s = 1.5f;
	ffdObj->setPoint(00, ffdObj->getPoint(00) + s * Vector((cos(time * 0.0018) * 10.0f), (sin(time * 0.0006) * 10.0f), (17.0f * sin(time * 0.0015))));
	ffdObj->setPoint(11, ffdObj->getPoint(11) + s * Vector((cos(time * 0.0009) * 16.0f), (sin(time * 0.0017) * 17.0f), (15.0f * cos(time * 0.0016))));
	ffdObj->setPoint(51, ffdObj->getPoint(51) + s * Vector((sin(time * 0.0017) * 13.0f), (sin(time * 0.0005) * 12.0f), (13.0f * sin(time * 0.0005))));
	ffdObj->setPoint(63, ffdObj->getPoint(63) + s * Vector((cos(time * 0.0007) * 17.0f), (cos(time * 0.0019) * 13.0f), (14.0f * cos(time * 0.0016))));
	s = 1.8f;
	ffdObj->setPoint(22, ffdObj->getPoint(22) + s * Vector((cos(time * 0.0018) * 13.0f), (sin(time * 0.0008) * 15.0f), (17.0f * sin(time * 0.0012))));
	ffdObj->setPoint(29, ffdObj->getPoint(29) + s * Vector((sin(time * 0.0020) * 15.0f), (cos(time * 0.0008) * 14.0f), (13.0f * sin(time * 0.0017))));
	ffdObj->setPoint(37, ffdObj->getPoint(37) + s * Vector((cos(time * 0.0016) * 16.0f), (cos(time * 0.0008) * 11.0f), (12.0f * cos(time * 0.0015))));
	ffdObj->setPoint(48, ffdObj->getPoint(48) + s * Vector((sin(time * 0.0017) * 13.0f), (sin(time * 0.0005) * 12.0f), (13.0f * sin(time * 0.0005))));

	Matrix view = Matrix().makeCamera(	Vector((float)cos(time * 0.0003) * 16.0f, (float)sin(time * 0.0005) * 20.0f + 5.0f, 45.0f + (float)sin(time * 0.0004) * 8.0f),
										Vector(0.0f, (float)sin(time * 0.0009) * 3.0f - 5.0f, 24.0f),
										Vector(0.0f, 1.0f, 0.0f));

	Matrix proj = Matrix().makePerspectiveProjection(60.0f, ASPECT, 1.0f, 1000.0f);

	scene.setProjection(proj);
	scene.setView(view);

	// render texture
	glh.clear();
	glh.setViewport(4, 25, RENDERTEXTURE_SIZEX - 8, RENDERTEXTURE_SIZEY - 50);

	if(time < 15900.0f) {
		glh.drawViewportQuad(texs[1 + (switchNoise % 3)], 1.5f * 1.333f, 1.5f, Vector(1.0f, 1.0f, 1.0f));
		glh.blend(0.1f, Vector(1.0f, 1.0f, 1.0f));
		switchNoise++;
	} else
		glh.renderScene(time, scene, true);

	glh.copyToTexture(renderTexture, 0, 0, RENDERTEXTURE_SIZEX, RENDERTEXTURE_SIZEY);

	view =		Matrix().makeCamera(	Vector((float)sin(time * 0.0003) * 20.0f, (float)sin(time * 0.0005) * 4.0f + 10.0f, 50.0f + (float)sin(time * 0.0004) * 5.0f),
										Vector((float)sin(time * 0.0006) * 5.0f, 0.0f, 39.0f + (float)sin(time * 0.0006) * 5.0f),
										Vector(0.0f, 1.0f, 0.0f));
	scene.setView(view);

	glh.clear();
	glh.setViewport(LEFT, BOTTOM, WIDTH, HEIGHT);
	glh.renderScene(time, scene);
}