#ifndef RECTANGLE_H
#define RECTANGLE_H

// Need this to know my base class
#include "GeomShape.h"

class Rectangle : public GeomShape
{
public:
	/// Rectangle with sides a and b
	Rectangle(double a, double b) : _a(a), _b(b) {}

	virtual double surface() override { return _a * _b; }
	virtual double circumference() override { return 2 * (_a + _b); }
	virtual std::string type() override { return "rectangle"; }

protected:
	/// My data are protected, becuase I do not want the outside to mess with them
	double _a, _b;
};

#endif
