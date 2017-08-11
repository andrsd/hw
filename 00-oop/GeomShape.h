#ifndef GEOMSHAPE_H
#define GEOMSHAPE_H

#include <string>

class GeomShape
{
public:
  GeomShape() { }

  // All my childs have to know their surface and circumference
  virtual double surface() = 0;
  virtual double circumference() = 0;
  // All my childs have to know who they are
  virtual std::string type() = 0;
};

#endif
