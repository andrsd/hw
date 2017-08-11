#include <vector>
#include <iostream>
#include "Vector.h"
#include "Matrix.h"

void vector_demo()
{
	Vector v;
	v.resize(3);
	v[0] = 1;
	v[1] = 3;
	v[2] = 2;

	std::cerr << "L2-norm is " << v.l2_norm() << std::endl;

	Vector u = v;
	std::cerr << "U = (" << u[0] << ", " << u[1] << ", " << u[2] << ")" << std::endl;

	Vector w = u;
	w.scale(2);
	std::cerr << "W = (" << w[0] << ", " << w[1] << ", " << w[2] << ")" << std::endl;
}

void matrix_demo()
{
	Matrix m(2, 2);
	m[0][0] = 1;
	m[1][1] = 1;

	std::cerr << "M = (" << m[0][0] << ", " << m[0][1] << std::endl;
	std::cerr << "     " << m[1][0] << ", " << m[1][1] << ")" << std::endl;

	Vector v(2);
	v[0] = 2;
	v[1] = 3;

	Vector r = m.mult(v);
	std::cerr << "R = (" << r[0] << ", " << r[1] << ")" << std::endl;
}

void global_ops()
{
	Vector v(2);
	v[0] = 2;
	v[1] = 3;

	Matrix m(2, 2);
	m[0][0] = 1;
	m[1][1] = 1;

	Vector r;
	r = m * v;

	std::cerr << "R = (" << r[0] << ", " << r[1] << ")" << std::endl;

	double sp = r * v;
	std::cout << "Scalar product = " << sp << std::endl;
}

int main()
{
	vector_demo();
	matrix_demo();
	global_ops();

	return 0;
}
