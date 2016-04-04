#ifndef H_VERTEX__
#define H_VERTEX__

#include "Vector.h"
#include <vector>

class Vertex {
public:
	Vertex();
	Vertex(Vector const& p);
	Vertex(Vector const& p, Vector const& n);

	Vector position;
	Vector normal;
	Vector texel;
};

typedef std::vector<Vertex> vertexList;

#endif