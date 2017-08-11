#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <cmath>

/// Note that for clarity we neglected all error checking
/// For simplicity, we are using std::vector to hold our data
/// but the underlying type can be anything we want. The interface
// would be the same and our example code would change
class Vector
{
public:
	/// Create an empty vector
	Vector() { }
	Vector(unsigned int n) { resize(n); }

	void resize(unsigned int new_size) { return _data.resize(new_size); }
	unsigned int size() const { return _data.size(); }

	void set(unsigned int idx, double data) { _data[idx] = data; }
	const double & get(unsigned int idx) const { return _data[idx]; }
	double & get(unsigned int idx) { return _data[idx]; }

	double l2_norm() {
		double sum = 0;
		for (auto k : _data)
			sum += k * k;
		return std::sqrt(sum);
	}

	const double & operator[](unsigned int idx) const { return get(idx); }
	double & operator[](unsigned int idx) { return get(idx); }

	// Even though _data is protected, we can access it directly, because any class
	// is a friend with itself
	void operator=(const Vector & v) {
		_data = v._data;
	}

	void scale(double s) {
		for (auto && k : _data)
			k *= s;
	}

	double scalar_product(const Vector & v) const {
		double sp = 0;
		for (unsigned int i = 0; i < v.size(); i++)
			sp += _data[i] * v._data[i];
		return sp;
	}

protected:
	std::vector<double> _data;
};

double operator*(const Vector & a, const Vector & b) { return a.scalar_product(b); }

#endif
