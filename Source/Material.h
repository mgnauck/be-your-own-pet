#ifndef H_MATERIAL__
#define H_MATERIAL__

#include "Vector.h"

class Material {
public:
	Material() {
		ambient			= Vector(0.2f, 0.2f, 0.2f);
		diffuse			= Vector(0.6f, 0.6f, 0.6f);
		specular		= Vector(0.0f, 0.0f, 0.0f);
		emissive		= Vector(0.0f, 0.0f, 0.0f);
		exponent		= 120.0f;
		texture			= -1;
		shadowCasting	= true;
		illuminated		= true;
		backfaces		= false;
	}

	Vector	ambient;
	Vector	diffuse;
	Vector	specular;
	Vector	emissive;
	float	exponent;
	int		texture;
	bool	shadowCasting;
	bool	illuminated;
	bool	backfaces;
};

#endif