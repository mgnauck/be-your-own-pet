#ifndef H_WALL__
#define H_WALL__

#include "Effect.h"

class Shape;

class Wall : public Effect {
public:
	Wall(float stime);
	void	run(float time);

private:
	float	update;
	int		texs[7];
	int		ovlSwitch;
	int		switchNoise;
	Shape*	shape;
};

#endif