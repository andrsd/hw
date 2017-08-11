#include <vector>
#include <iostream>
#include "GeomShape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"

/// Add random elements into `array`
void fill(std::vector<GeomShape *> & array)
{
	array.push_back(new Rectangle(2, 3));
	array.push_back(new Circle(1));
	array.push_back(new Circle(3));
	array.push_back(new Rectangle(5, 3));
	array.push_back(new Square(3));
}

int main()
{
	// An array of our shape without knowing what they actually are
	std::vector<GeomShape *> shapes;

	fill(shapes);

	// Compute the total surface
	double total_surface = 0;
	for (auto i : shapes)
		total_surface += i->surface();
	std::cout << "Total surface = " << total_surface << std::endl;

	// Talk to me my shapes!
	for (auto i : shapes)
		std::cout << "I am a " << i->type() << " and my circumference is " << i->circumference() << std::endl;

	return 0;
}
