#pragma once
#include "Point.h"
#include <vector>

namespace Spline
{
   class Spline
   {
   public:
      virtual void update(const std::vector<Point> &p, const std::vector<double> &value) = 0;
      virtual std::vector<double> get_value(const Point &p) const = 0;
   };
}