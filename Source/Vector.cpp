#include "Vector.h"
#include "Intro.h"
#include <cmath>

float const PI = 3.14159265f;
float const EPSILON = 0.0001f;
float const DEG2RAD = PI / 180.0f;
float const RAD2DEG = 180.0f / PI;

Vector::Vector() : w(1.0f) {}

Vector::Vector(float a, float b, float c) : x(a), y(b), z(c), w(1.0f) {}

Vector::Vector(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}

float Vector::dot(Vector const& rhs) const {
	return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector Vector::cross(Vector const& rhs) {
	return Vector(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

float Vector::length2() const {
	return dot(*this);
}

float Vector::length() const {
	return sqrtf(length2());
}

void Vector::normalize() {
	float t = 1.0f / length();
	x *= t;
	y *= t;
	z *= t;
}

Vector Vector::normalized() const {
	Vector t(*this);
	t.normalize();
	return t;
}

Vector Vector::rand() const {
	float z = rnd(-1.0f, 1.0f);
	float t = rnd(0.0f, 2.0f * PI);
	float r = sqrt(1.0f - z * z);
	return Vector(r * cos(t), r * sin(t), z);
}

Vector Vector::operator-() const {
	return Vector(-x, -y, -z);
}

Vector const& Vector::operator-=(Vector const& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector const& Vector::operator+=(Vector const& rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector const& Vector::operator*=(float rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}

float const Vector::operator()(int n) const {
	switch(n) {
		case 0:		return x;
		case 1:		return y;
		case 2:		return z;
		default:	return w;
	}
}

float& Vector::operator()(int n) {
	switch(n) {
		case 0:		return x;
		case 1:		return y;
		case 2:		return z;
		default:	return w;
	}
}

Vector operator+(Vector const& lhs, Vector const& rhs) {
	Vector t(lhs);
	t += rhs;
	return t;
}

Vector operator-(Vector const& lhs, Vector const& rhs) {
	Vector t(lhs);
	t -= rhs;
	return t;
}

Vector operator*(Vector const& lhs, float rhs) {
	Vector t(lhs);
	t *= rhs;
	return t;
}

Vector operator*(float lhs, Vector const& rhs) {
	Vector t(rhs);
	t *= lhs;
	return t;
}

bool operator==(Vector const& lhs, Vector const& rhs){
	if(	(abs(lhs.x - rhs.x) < EPSILON) &&
		(abs(lhs.y - rhs.y) < EPSILON) &&
		(abs(lhs.z - rhs.z) < EPSILON)	)
		return true;
	
	return false;
}

bool operator!=(Vector const& lhs, Vector const& rhs){
	return !(lhs == rhs);
}

/*
std::ostream& operator<<(std::ostream& os, Vector const& v) {
	os << v(0) << " " << v(1) << " " << v(2) << " " << v(3) << std::endl;
	return os;
}*/