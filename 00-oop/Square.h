#ifndef SQUARE_H
#define SQUARE_H

// Need this to know my base class
#include "Rectangle.h"

class Square : public Rectangle
{
public:
	/// Square with a side is a special case of Rectangle
	Square(double a) : Rectangle(a, a) {}

	/// I am distinguishing myself form a rectangle
	virtual std::string type() override { return "square"; }
};

#endif
