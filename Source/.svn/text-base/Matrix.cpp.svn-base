#include "Matrix.h"
#include <cmath>
#include <cassert>

Matrix::Matrix(bool id) {
	if(id)
		makeIdentity();
}

void Matrix::makeZero() {
	for(int j=0; j<4; j++)
		for(int i=0; i<4; i++)
			m[j][i] = 0.0f;
}

void Matrix::makeIdentity() {
	makeZero();
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
}

Matrix Matrix::identity() const {
	Matrix t;
	t.makeIdentity();
	return t;
}

void Matrix::transpose() {
	Matrix t(*this);
	for(int j=0; j<4; j++)
		for(int i=0; i<4; i++)
			m[i][j] = t.m[j][i];
}

Matrix Matrix::transposed() const {
	Matrix t(*this);
	t.transpose();
	return t;
}

Matrix const& Matrix::setRow3(int n, Vector const& v) {
	m[n][0] = v.x;
	m[n][1] = v.y;
	m[n][2] = v.z;
	return *this;
}

Vector Matrix::getRow3(int n) const {
	return Vector(m[n][0], m[n][1], m[n][2]);
}

Matrix const& Matrix::setCol3(int n, Vector const& v) {
	m[0][n] = v.x;
	m[1][n] = v.y;
	m[2][n] = v.z;
	return *this;
}

Vector Matrix::getCol3(int n) const {
	return Vector(m[0][n], m[1][n], m[2][n]);
}

Matrix& Matrix::makeRotation(Vector const& axis, float angle) {
	// ass axis norm!
	float	sina	= sin(angle);
	float	cosa	= cos(angle);
	float	cosa1	= 1.0f - cosa;
	float	xy		= axis.x * axis.y;
	float	xz		= axis.x * axis.z;
	float	yz		= axis.y * axis.z;
	float	xsina	= axis.x * sina;
	float	ysina	= axis.y * sina;
	float	zsina	= axis.z * sina;

	m[0][0] = cosa + axis.x * axis.x * cosa1;
	m[1][0] = zsina + xy * cosa1;
	m[2][0] = -ysina + xz * cosa1;
	m[0][1] = -zsina + xy * cosa1;
	m[1][1] = cosa + axis.y * axis.y * cosa1;
	m[2][1] = xsina + yz * cosa1;
	m[0][2] = ysina + xz * cosa1;
	m[1][2] = -xsina + yz * cosa1;
	m[2][2] = cosa + axis.z * axis.z * cosa1;

	m[3][0] = m[3][1] = m[3][2] = m[0][3] = m[1][3] = m[2][3] = 0.0f;
	m[3][3] = 1.0f;

	return *this;
}


Matrix& Matrix::makePerspectiveProjection(float fov, float aspect, float n, float f) {

/*

	2*near/(right-left)				0				(right+left)/(right-left)				0
	0						2*near/(top-bottom)		(top+bottom)/(top-bottom)				0
	0								0				-(far+near)/(far-near)		-2*far*near/(far-near)
	0								0						-1								0

*/

	float	y		= n * tan(fov * PI / 360.0f);
	float	x		= y * aspect;

	float	top		=  y;
	float	bottom	= -y;
	float	left	= -x;
	float	right	=  x;

	assert(left != right);
	assert(bottom != top);
	assert(n != f);

	m[0][0] = 2.0f * n / (right - left);
	m[0][1] = 0.0f;
	m[0][2] = (right + left) / (right - left);
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 2.0f * n / (top - bottom);
	m[1][2] = (top + bottom) / (top - bottom);
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = -(f + n) / (f - n);
	m[2][3] = -2.0f * f * n / (f - n);

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = -1.0f;
	m[3][3] = 0.0f;

	return *this;
}

Matrix& Matrix::makeOrthogonalProjection(float l, float b, float r, float t, float n, float f) {

/*

	2 / (right - left)		0							0				(right + left) / (right - left)
			0				2 / (top - bottom)			0				(top + bottom) / (top - bottom)
			0					0					-2 / (far - near)		(far + near) / (far - near)
			0					0							0							1

*/

	float	width	= r - l;
	float	height	= t - b;
	float	depth	= f - n;

	assert(width != 0.0f);
	assert(height != 0.0f);
	assert(depth != 0.0f);

	makeZero();

	// scale
	m[0][0] = 2.0f / width;
	m[1][1] = 2.0f / height;
	m[2][2] = -2.0f / depth;
	m[3][3] = 1.0f;

	// translation
	m[1][3] = (l + r) / width;
	m[2][3] = (b + t) / height;
	m[3][3] = (n + f) / depth;

	return *this;
}

Matrix& Matrix::makeCamera(Vector const& e, Vector const& t, Vector const& u) {

	Vector fw(e - t);
	fw.normalize();

	Vector up(u);
	Vector ri = up.cross(fw);
	ri.normalize();

	up = fw.cross(ri);
	up.normalize();

	Matrix rot;
	rot.makeIdentity();
	rot.setRow3(0, ri);
	rot.setRow3(1, up);
	rot.setRow3(2, fw);

	Matrix trans;
	trans.makeIdentity();
	trans.setCol3(3, -e);

	*this = rot * trans;
	return *this;
}

float Matrix::det2x2(float a, float b, float c, float d) const {

	// a b
	// c d
	return (a * d) - (b * c);
}

float Matrix::det3x3(float a1, float b1, float c1, float a2, float b2, float c2, float a3, float b3, float c3) const {

	// a1 b1 c1
	// a2 b2 c2
	// a3 b3 c3
	return a1 * b2 * c3 + a2 * b3 * c1 + a3 * b1 * c2 - c1 * b2 * a3 - c2 * b3 * a1 - c3 * b1 * a2;
}

float Matrix::det() const {

	// laplacescher entwicklungssatz, entwicklung nach der ersten (=0) zeile
	// (es wird immer die j-te spalte und die entwicklungszeile gestrichen)
	// vorzeichen wechsel schachbrettartig (-1^(i+j))

	float d;

	// jeweils 0te/1te/.. spalte gestrichen
	d  = m[0][0] * det3x3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3],	m[3][1], m[3][2], m[3][3]);
	d -= m[0][1] * det3x3(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3],	m[3][0], m[3][2], m[3][3]);
	d += m[0][2] * det3x3(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3],	m[3][0], m[3][1], m[3][3]);
	d -= m[0][3] * det3x3(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2],	m[3][0], m[3][1], m[3][2]);

	return d;
}

Matrix Matrix::inverted() const {

	// inverse = ( 1 / detA ) * transpose(Aadj)
	// Aadj = (-1)^(i+j) * det(Aij) (Aij = A mit ite-zeile & jte-spalte gestrichen)

	float d = det();

	assert(d != 0.0f);	// = nicht regular = nicht invertierbar

	Matrix inv;

	inv.m[0][0] =  det3x3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
	inv.m[0][1] = -det3x3(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
	inv.m[0][2] =  det3x3(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
	inv.m[0][3] = -det3x3(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

	inv.m[1][0] = -det3x3(m[0][1], m[0][2], m[0][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
	inv.m[1][1] =  det3x3(m[0][0], m[0][2], m[0][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
	inv.m[1][2] = -det3x3(m[0][0], m[0][1], m[0][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
	inv.m[1][3] =  det3x3(m[0][0], m[0][1], m[0][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

	inv.m[2][0] =  det3x3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[3][1], m[3][2], m[3][3]);
	inv.m[2][1] = -det3x3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[3][0], m[3][2], m[3][3]);
	inv.m[2][2] =  det3x3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[3][0], m[3][1], m[3][3]);
	inv.m[2][3] = -det3x3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[3][0], m[3][1], m[3][2]);

	inv.m[3][0] = -det3x3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3]);
	inv.m[3][1] =  det3x3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3]);
	inv.m[3][2] = -det3x3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3]);
	inv.m[3][3] =  det3x3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);

	inv.transpose();
	inv *= 1.0f / d;

	return inv;
}

Matrix const& Matrix::operator+=(Matrix const& rhs) {
	for(int j=0; j<4; j++)
		for(int i=0; i<4; i++)
			m[j][i] += rhs.m[j][i];
	return *this;
}

Matrix Matrix::operator-() const {
	Matrix t;
	for(int j=0; j<4; j++)
		for(int i=0; i<4; i++)
			t.m[j][i] = -m[j][i];
	return t;
}

Matrix const& Matrix::operator-=(Matrix const& rhs) {
	for(int j=0; j<4; j++)
		for(int i=0; i<4; i++)
			m[j][i] -= rhs.m[j][i];
	return *this;
}

Matrix const& Matrix::operator*=(Matrix const& rhs) {
	Matrix t;
	for(int k=0; k<4; k++) {
		for(int j=0; j<4; j++) {
			float sum = 0.0f;
			for(int i=0; i<4; i++)
				sum += m[j][i] * rhs.m[i][k];
			t.m[j][k] = sum;
		}
	}
	*this = t;
	return *this;
}

Matrix const& Matrix::operator*=(float rhs) {
	for(int j=0; j<4; j++)
		for(int i=0; i<4; i++)
			m[j][i] *= rhs;
	return *this;
}

float const	Matrix::operator()(int row, int col) const {
	return m[row][col];
}

float& Matrix::operator()(int row, int col) {
	return m[row][col];
}

Matrix operator+(Matrix const& lhs, Matrix const& rhs) {
	Matrix t(lhs);
	t += rhs;
	return t;
}

Matrix operator-(Matrix const& lhs, Matrix const& rhs) {
	Matrix t(lhs);
	t -= rhs;
	return t;
}

Matrix operator*(Matrix const& lhs, Matrix const& rhs) {
	Matrix t(lhs);
	t *= rhs;
	return t;
}

Vector operator*(Matrix const& lhs, Vector const& rhs) {
	Vector t;
	for(int j=0; j<4; j++) {
		float sum = 0.0f;
		for(int i=0; i<4; i++)
			sum += lhs(j, i) * rhs(i);
		t(j) = sum;
	}
	return t;
}

Matrix operator*(Matrix const& lhs, float rhs) {
	Matrix t(lhs);
	t *= rhs;
	return t;
}

Matrix operator*(float lhs, Matrix const& rhs) {
	Matrix t(rhs);
	t *= lhs;
	return t;
}

bool operator==(Matrix const& lhs, Matrix const& rhs) {
	for(int j=0; j<4; j++)
		for(int i=0; i<4; i++)
			if(abs(lhs.m[j][i] - rhs.m[j][i]) > EPSILON)
				return false;
	return true;
}

bool operator!=(Matrix const& lhs, Matrix const& rhs) {
	return !(lhs == rhs);
}

/*
std::ostream& operator<<(std::ostream& os, Matrix const& m) {
	for(int j=0; j<4; j++)
		os << m(j, 0) << ", " << m(j, 1) << ", " << m(j, 2) << ", " << m(j, 3) << std::endl;
	return os;
}
*/