#include "Triangle.h"

Triangle::Triangle() {}

Triangle::Triangle(int i1, int i2, int i3) : a(i1), b(i2), c(i3) {}

void Triangle::calcNormal(Vector const& v1, Vector const& v2, Vector const& v3) {
	normal = (v2 - v1).cross(v3 - v1);
	normal.normalized();
}