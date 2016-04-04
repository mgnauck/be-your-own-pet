#ifndef H_TWINE__
#define H_TWINE__

#include "Effect.h"

class Shape;

#define SPLINE_COUNT	12
#define PIECE_COUNT		20

class Twine : public Effect {
public:
	Twine(float stime);
	void	run(float time);

private:
	Shape*	shape[SPLINE_COUNT];
	float	update;
	float	t;
	int		actGrow;

};

#endif