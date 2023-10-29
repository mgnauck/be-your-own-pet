#ifndef H_LIGHT__
#define H_LIGHT__

#include <vector>
#include "Vector.h"
#include "Intro.h"

class Light {
public:
	Light(Vector const& c, Vector const& p, int cnt, float scatterRad) : color(c), position(p) {
		for(int i=0; i<cnt; i++)
			samples.push_back(position + Vector(rnd(-scatterRad, scatterRad), 0.0f, rnd(-scatterRad, scatterRad)));
	}

	~Light() {
		samples.clear();
	}

	Vector		color;
	Vector		position;
	vectorList	samples;
};

#endif