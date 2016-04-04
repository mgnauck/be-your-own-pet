#include "Spline.h"

Spline::Spline(int deg) : degree(deg), valid(false) {
	points.reserve(20);
	knot.reserve(20 + degree + degree);
	valid = false;
}

Spline::~Spline() {
	points.clear();
	knot.clear();
}

void Spline::addPoint(Vertex const& v) {
	points.push_back(v);
	valid = false;
}

void Spline::setPoint(int n, Vector const& v) {
	points[n].position = v;
}

Vertex Spline::eval(float t) {

	// recalc knot if necessary
	if(!valid)
		calcKnotVec();

	// we do not want to cross intervall borders
	//assert( t < knot[knot.size() - degree - 1] );
	if(t > knot[knot.size() - degree - 1])
		t = knot[knot.size() - degree - 1] - EPSILON;
	
	// init pos & normal with zero
	Vertex v(Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f));

	//v.texel = Vector(0.0f, 0.0f, 0.0f);

	// sum up the blending functions that have infulence
	for(int i=0; i<getCount(); i++) {
		float influence = coxDeBoor(i, degree, t);
		if(influence == 0.0f)
			continue;
		v.position += points[i].position * influence;
		v.normal += points[i].normal * influence;
		//v.texel += points[i].texel * influence;
	}

	v.normal.normalize();

	return v;
}

int Spline::getCount() const{
	return (int)points.size();
}

float Spline::getIntervallStart() {
	// recalc knot if necessary
	if(!valid)
		calcKnotVec();
	return knot[degree];
}

float Spline::getIntervallEnd() {
	// recalc knot if necessary
	if(!valid)
		calcKnotVec();
	return knot[knot.size() - degree - 1] - EPSILON;
}

Vertex const& Spline::getPoint(int n) const {
	return points[n];
}

void Spline::calcKnotVec() {

	knot.clear();

	// calc simple knot
	// only first & last point get higher multiplicity
	for(int i=0; i<getCount() + degree + 1; i++) {
		
		float val;
		if(i <= degree)
			val = 0.0f;
		else if(i >= (getCount() + 1))
			val = (float)(getCount() - degree);
		else
			val = (float)(i - degree);

		knot.push_back(val);
	}

	valid = true;
}

float Spline::coxDeBoor(int i, int n, float t) {

	// degree = 0
	if(n == 0) {
		if((t >= knot[i]) && (t < knot[i + 1]))
			return 1.0;
		else
			return 0.0;
	}
	
	// degree > 0
	float ti		= knot[i];
	float tin		= knot[i + n];
	float tip1		= knot[i + 1];
	float tinp1		= knot[i + n + 1];
	
	float tinti		= (tin - ti);
	float tinp1tip1	= (tinp1 - tip1);

	float val1		= 0.0f;
	float val2		= 0.0f;

	if(tinti != 0.0f)
		val1 = ((t - ti) / tinti) * coxDeBoor(i, n - 1, t);

	if(tinp1tip1 != 0.0f)
		val2 = ((tinp1 - t) / tinp1tip1) * coxDeBoor(i + 1, n - 1, t);

	return val1 + val2;
}