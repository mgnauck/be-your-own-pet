#ifndef H_DEFORMATOR__
#define H_DEFORMATOR__

#include "Effect.h"

class FFDObject;
class Mesh;

class Deformator : public Effect {
public:
	Deformator(float stime);
	void		run(float time);

private:
	FFDObject*	ffdObj;
	float		update;
	int			pointNum;
	bool		on;
	float		t;
	int			texs[4];
	int			switchNoise;
	Mesh*		planeLe[6];
	Mesh*		planeRi[6];
};

#endif