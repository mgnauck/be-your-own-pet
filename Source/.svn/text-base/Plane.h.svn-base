#ifndef H_PLANE__
#define H_PLANE__

#include "Vector.h"

class Plane {
public:
	Plane(Vector const& n, float d, bool normalize = false) : dist(d), nrm(n) {
		if(normalize)
			nrm.normalize();
	}

	Vector	nrm;
	float	dist;
};

#endif