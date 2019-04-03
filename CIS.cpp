#include "CIS.h"
#include <iostream>
#include <math.h>

namespace Spline
{
   void CIS::update(const std::vector<Point>& p, const std::vector<double> &value)
   {
      points.clear();
      for (auto elem : p)
         points.push_back(elem);

      size_t segment_num = p.size() - 1;
      double h_cur, h_next;

      a.resize(segment_num);
      b.resize(segment_num);
      c.resize(segment_num + 1);
      d.resize(segment_num);

      for (size_t i = 1; i < segment_num; i++)
      {
         h_cur = p[i].get_x() - p[i - 1].get_x();
         h_next = p[i + 1].get_x() - p[i].get_x();

         a[i] = h_cur;
         b[i - 1] = 2 * (h_cur + h_next);
         c[i - 1] = 3.0 * ((value[i + 1] - value[i]) / h_next - (value[i] - value[i - 1]) / h_cur);
         d[i - 1] = h_next;
      }

      for (size_t i = 1; i < segment_num - 1; i++)
      {
         b[i] -= a[i] / b[i - 1] * d[i - 1];
         c[i] -= a[i] / b[i - 1] * c[i - 1];
      }

      c[segment_num - 1] /= b[segment_num - 2];
      for (size_t i = segment_num - 3; i >= 0; i--)
         c[i] = (c[i] - c[i + 1] * d[i]) / b[i];

      c[segment_num] = 0.0;
      for (size_t i = segment_num - 1; i > 0; i--)
         c[i] = c[i - 1];
      c[0] = 0.0;

      for (size_t i = 0; i < segment_num; i++)
      {
         h_cur = p[i + 1].get_x() - p[i].get_x();
         a[i] = value[i];
         b[i] = (value[i + 1] - value[i]) / h_cur - (c[i + 1] + 2.0 * c[i]) * h_cur / 3.0;
         d[i] = (c[i + 1] - c[i]) / h_cur / 3.0;
      }
   }

   std::vector<double> CIS::get_value(const Point &p) const
   {
      double eps = 1e-7;
      size_t segment_num = points.size() - 1;
      double elem = p.get_x();
	  std::vector<double> result (3,0);

      for (size_t i = 0; i < segment_num; i++)
         if (elem > points[i].get_x() && elem < points[i + 1].get_x() || fabs(elem - points[i].get_x()) < eps ||
            fabs(elem - points[i + 1].get_x()) < eps)
         {
            double diff = fabs(elem - points[i].get_x());
            result[0] = a[i] + b[i] * diff + c[i] * pow(diff, 2) + d[i] * pow(diff, 3);
            result[1] = b[i] + 2.0 * c[i] * diff + 3.0 * d[i] * pow(diff, 2);
            result[2] = 2.0 * c[i] + 6.0 * d[i] * diff;
            return result;
         }

      throw std::exception("The point wasn't found");
   }
}