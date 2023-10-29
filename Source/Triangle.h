#ifndef H_TRIANGLE__
#define H_TRIANGLE__

#include "Vector.h"
#include <vector>

struct RenderTriangle {
	int a, b, c;
};

class Triangle {
public:
	Triangle();
	Triangle(int i1, int i2, int i3);

	void calcNormal(Vector const& v1, Vector const& v2, Vector const& v3);

	int		a, b, c;
	Vector	normal;
};

typedef std::vector<Triangle>		triangleList;
typedef std::vector<RenderTriangle>	renderTriangleList;

#endif