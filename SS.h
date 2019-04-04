#pragma once
#include "Spline.h"
#include <exception> // std::exception

namespace Spline
{
   class SS : public Spline
   {
   private:
      double smooth;
      std::vector<Point> points;
      std::vector<double> alpha;

      void master_element(size_t segment_num, const double &x, double &ksi) const;
      double basic(char num, const double &ksi) const;
      double der_basic(char num, const double &ksi) const;
   public:
      SS(const double &s) : smooth(s) {};
      void update(const std::vector<Point> &p, const std::vector<double> &value) override;
	  std::vector<double> get_value(const Point &p) const override;
   };
}