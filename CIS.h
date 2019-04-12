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
      void update(const std::vector<double> &value) override;
      std::vector<double> get_value(const Point &p) const override;

      std::vector<double> regular(double a, double b, size_t n) override;
      std::vector<double> adaptive(double a, double b, double r, size_t n) override;
   };
}