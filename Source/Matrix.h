#ifndef H_MATRIX__
#define H_MATRIX__

#include "Vector.h"

class Matrix {
public:
	Matrix(bool id = false);

	void			makeZero();
	void			makeIdentity();
	Matrix			identity() const;

	void			transpose();
	Matrix			transposed() const;

	Matrix const&	setRow3(int n, Vector const& v);		// 3 means w component is
	Vector			getRow3(int n) const;					// omitted
	Matrix const&	setCol3(int n, Vector const& v);
	Vector			getCol3(int n) const;

	Matrix&			makeRotation(Vector const& axis, float angle);
	Matrix&			makePerspectiveProjection(float fov, float aspect, float n, float f);
	Matrix&			makeOrthogonalProjection(float l, float b, float r, float t, float n, float f);
	Matrix&			makeCamera(Vector const& e, Vector const& t, Vector const& u);

	float			det2x2(float a, float b, float c, float d) const;
	float			det3x3(float a1, float b1, float c1, float a2, float b2, float c2, float a3, float b3, float c3) const;
	float			det() const;
	Matrix			inverted() const;

	Matrix const&	operator+=(Matrix const& rhs);
	Matrix			operator -() const;
	Matrix const&	operator-=(Matrix const& rhs);
	Matrix const&	operator*=(Matrix const& rhs);
	Matrix const&	operator*=(float rhs);

	float const		operator()(int row, int col) const;
	float&			operator()(int row, int col);

	float			m[4][4];
};

Matrix operator+(Matrix const& lhs, Matrix const& rhs);
Matrix operator-(Matrix const& lhs, Matrix const& rhs);
Matrix operator*(Matrix const& lhs, Matrix const& rhs);
Vector operator*(Matrix const& lhs, Vector const& rhs);
Matrix operator*(Matrix const& lhs, float rhs);
Matrix operator*(float lhs, Matrix const& rhs);

bool operator==(Matrix const& lhs, Matrix const& rhs);
bool operator!=(Matrix const& lhs, Matrix const& rhs);

//std::ostream& operator<<(std::ostream& os, Matrix const& rhs);

#endif