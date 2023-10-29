#ifndef H_EFFECTPLAYER__
#define H_EFFECTPLAYER__

#include "GLHelper.h"

class First;
class Wall;
class Twine;
class Deformator;
class Spiral;
class SpermWorm;

class EffectPlayer {
public:
	EffectPlayer();
	
	void		run(float time);
	bool		isRunning() const;

	void		showTitleOverlay(float time);
	void		fades(float time);

private:
	GLHelper	glh;
	bool		running;
	int			ovl;

	First*		first;
	Wall*		wall;
	Twine*		twine;
	Deformator*	deformator;
	Spiral*		spiral;
	SpermWorm*	spermWorm;
};

#endif