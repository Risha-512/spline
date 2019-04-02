#pragma once
#include "Spline.h"

namespace Spline
{
   class CIS : public Spline
   {
   private:
      std::vector<Point> points;
      std::vector<double> a, b, c, d;
   public:
      void update(const std::vector<Point> &p, const std::vector<double> &value) override;
      void get_value(const Point &p, double *result) const override;
   };
}