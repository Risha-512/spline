#pragma once
#include "Point.h"
#include <vector>

namespace Spline
{
   class Spline
   {
   public:
      virtual void update_spline(const std::vector<Point> &points, const std::vector<double> &func_value) = 0;
      virtual void get_value(const Point &point, double *result) const = 0;
   };
}