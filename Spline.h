#pragma once
#include "Point.h"
#include <vector>
#include <cmath>

namespace Spline
{
   class Spline
   {
   public:
      virtual void update(const std::vector<double> &value) = 0;
      virtual std::vector<double> get_value(const Point &p) const = 0;
      
      virtual std::vector<double> regular(double a, double b, size_t n) = 0;
      virtual std::vector<double> adaptive(double a, double b, double r, size_t n) = 0;      // actually I don't know when we should use this function
   };
}