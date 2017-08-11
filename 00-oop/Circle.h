#ifndef CIRCLE_H
#define CIRCLE_H

// Need this to know my base class
#include "GeomShape.h"

// Ludolph's number
#define PI  3.1415

class Circle : public GeomShape
{
public:
	/// Circle with radius r
	Circle(double r) : _r(r) {}

	virtual double surface() override { return PI * _r * _r; }
	virtual double circumference() override { return 2 * PI * _r; }
	virtual std::string type() override { return "circle"; }

protected:
	/// My radius is protected, becuase I do not want the outside to mess with it
	/// And it is not private, becuase I want my (eventual) childs to use my radius
	double _r;
};

#endif
