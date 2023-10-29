#include "EffectPlayer.h"
#include "Intro.h"
#include "Map.h"
#include "First.h"
#include "SpermWorm.h"
#include "Deformator.h"
#include "Spiral.h"
#include "Twine.h"
#include "Wall.h"
#include <cmath>

#include "../data/title.h"
#include "../data/gfx.h"
#include "../data/music.h"
#include "../data/code.h"

#define WALL_MAEN_TIME	136868.f

EffectPlayer::EffectPlayer() : running(true) {

	Map* m;

	renderTexture	= GLHelper().createRenderTexture(RENDERTEXTURE_SIZEX, RENDERTEXTURE_SIZEY);

	// upload ovls 
	m = load_from_h(title, title_width, title_height, true);
	ovl = GLHelper().uploadTexture(*m, true);
	delete m;
	
	// init effects
	srand(0xaf9d0212);
	first		= new First(0.0f);
	twine		= new Twine(8940.f);
	deformator	= new Deformator(40892.0f);
	srand(0xef6abc2a);
	spiral		= new Spiral(72884.0f);
	srand(0xedab5a2a);
	spermWorm	= new SpermWorm(104897.0f);
	wall		= new Wall(WALL_MAEN_TIME);		// 138000
}


// ab hier geht sau der scheiss kode
// aber im mom tick ich einfach nix anderes

void EffectPlayer::run(float time) {

	if(time >= first->getStartTime() && time < twine->getStartTime())
		first->run(time - first->getStartTime());
		
	if(time >= twine->getStartTime() && time < deformator->getStartTime())
		twine->run(time - twine->getStartTime());

	if(time >= deformator->getStartTime() && time < spiral->getStartTime())
		deformator->run(time - deformator->getStartTime());

	if(time >= spiral->getStartTime() && time < spermWorm->getStartTime())
		spiral->run(time - spiral->getStartTime());

	if(time >= spermWorm->getStartTime() && time < wall->getStartTime())
		spermWorm->run(time - spermWorm->getStartTime());

	if(time >= wall->getStartTime() && time < 168861.f)
		wall->run(time - wall->getStartTime());

	if(time > 168861.f) {
	//if(time > 168000.0f) {
		glh.clear();
		running = false;
	}

	showTitleOverlay(time);
	fades(time);
}

void EffectPlayer::showTitleOverlay(float time) {

	static float a	= 0.0f;
	static float au	= 0.0f;
	static float bu	= 0.0f;

	// title
	if(time > 23000.0f && time < 40000.0f) {

		if(a < 1.0f && time < 28000.0f && time - au > 50.0f) {
			a += 0.03f;
			au = time;
		}

		if(a > 0.0f && time > 32500.0f && time - bu > 50.0f) {
			a -= 0.05f;
			bu = time;
		}

		glViewport(LEFT, BOTTOM, WIDTH, HEIGHT);
		glh.drawOvl(ovl, -0.8f, -0.8f, 0.5f, 0.5f, a);
	}
}

void EffectPlayer::fades(float time) {

	static float a	= 1.0f;
	static float b	= 0.0f;
	static float c	= 0.0f;
	static float d	= 0.0f;
	static float e	= 0.0f;
	static float au	= 0.0f;
	static float bu	= 0.0f;
	static float cu	= 0.0f;
	static float du	= 0.0f;
	static float eu	= 0.0f;

	glViewport(LEFT, BOTTOM, WIDTH, HEIGHT);
	
	// fade in anfang
	if(time > 0.0f && time < 8000.0f) {
		if(time > 4000.0f && time - au > 50.0f) {
			a -= 0.02f;
			au = time;
		}
		glh.blend(a, Vector(0.0f, 0.0f, 0.0f));
	}

	// fade out chill part
	if(time > 102500.0f && time < 104897.0f) {
		if(time - cu > 50.0f && c < 1.0f) {
			c += 0.04f;
			cu = time;
		}
		glh.blend(c, Vector(0.0f, 0.0f, 0.0f));
	}

	// fade weiss hoch spermworm part
	if(time > (WALL_MAEN_TIME-1368.f) && time < WALL_MAEN_TIME) {
		if(time - du > 50.0f && d < 1.0f) {
			d += 0.04f;
			du = time;
		}
		glh.blend(d, Vector(1.0f, 1.0f, 1.0f));
	}

	// fade weiss runter nachm spermworm
	if(time > WALL_MAEN_TIME && time < (WALL_MAEN_TIME+1368.f)) {
		if(time - eu > 50.0f && e > 0.0f) {
			e -= 0.04f;
			eu = time;
		}
		glh.blend(e, Vector(1.0f, 1.0f, 1.0f));
	}

	// fade out ende
	if(time > 154000.0f) {
		if(time - bu > 50.0f) {
			b += 0.02f;
			bu = time;
		}
		glh.blend(b, Vector(0.0f, 0.0f, 0.0f));
	}

}

bool EffectPlayer::isRunning() const {
	return running;
}