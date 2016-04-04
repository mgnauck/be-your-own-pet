#ifndef H_SPLINE__
#define H_SPLINE__

#include <vector>
#include "Vertex.h"

// basic implementation of non-uniform bspline
class Spline {
public:
	Spline(int degree);
	virtual ~Spline();

	void				addPoint(Vertex const& v );
	void				setPoint(int n, Vector const& v);
	Vertex				eval(float t);

	int					getCount() const;
	float				getIntervallStart();
	float				getIntervallEnd();

	Vertex const&		getPoint(int n) const;

protected:
	void				calcKnotVec();
	float				coxDeBoor(int i, int n, float t);

	int					degree;
	bool				valid;

	std::vector<Vertex>	points;
	std::vector<float>	knot;
};

#endif