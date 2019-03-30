#pragma once
#include "Spline.h"

namespace Spline
{
   class CIS : public Spline
   {
   private:
      std::vector<Point> points;
      std::vector<double> A, B, C, D;
   public:
      void update_spline(const std::vector<Point> &P, const std::vector<double> &func_value) override;
      void get_value(const Point &point, double *result) const override;

   };
}