#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
public:
	Matrix(unsigned int m, unsigned int n) {
		_data.resize(m);
		for (auto && k : _data)
			k.resize(n);
	}

	void set(unsigned int i, unsigned int j, double v) { _data[i][j] = v; }
	double get(unsigned int i, unsigned int j) { return _data[i][j]; }

	std::vector<double> & operator[](unsigned int i) { return _data[i]; }

	Vector mult(const Vector & v) const {
		unsigned int n = v.size();
		Vector result(n);
		for (unsigned int i = 0; i < n; i++)
			for (unsigned int j = 0; j < n; j++)
				result[i] += _data[i][j] * v[j];
		return result;
	}

protected:
	std::vector<std::vector<double>> _data;
};


Vector operator*(const Matrix & m, const Vector & v) { return m.mult(v); }

#endif
