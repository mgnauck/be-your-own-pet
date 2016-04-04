#ifndef H_VECTOR__
#define H_VECTOR__

//#include <iostream>
#include <vector>

class Vector {
public:
	Vector();
	Vector(float a, float b, float c);
	Vector(float a, float b, float c, float d);

	float			dot(Vector const& rhs) const;
	Vector			cross(Vector const& rhs);

	float			length2() const;
	float			length() const;

	void			normalize();
	Vector			normalized() const;
	Vector			rand() const;					// rand point on unit sphere

	Vector			operator-() const;
	Vector const&	operator-=(Vector const& rhs);
	Vector const&	operator+=(Vector const& rhs);
	Vector const&	operator*=(float rhs);

	float const		operator()(int n) const;		// slow shit!
	float&			operator()(int n);

	float			x, y, z, w;
};

extern float const PI;
extern float const EPSILON;
extern float const DEG2RAD;
extern float const RAD2DEG;

Vector operator+(Vector const& lhs, Vector const& rhs);
Vector operator-(Vector const& lhs, Vector const& rhs);
Vector operator*(Vector const& lhs, float rhs);
Vector operator*(float lhs, Vector const& rhs);

bool operator==(Vector const& lhs, Vector const& rhs);
bool operator!=(Vector const& lhs, Vector const& rhs);

//std::ostream& operator<<(std::ostream& os, Vector const& rhs);

typedef std::vector<Vector> vectorList;

#endif