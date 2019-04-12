#include "CIS.h"

namespace Spline
{
   void CIS::update(const std::vector<double> &value)
   {
      if (points.empty())
         throw std::runtime_error("Vector of points is empty");

      size_t segment_num = points.size() - 1;
      double h_cur, h_next;

      a.resize(segment_num);
      b.resize(segment_num);
      c.resize(segment_num + 1);
      d.resize(segment_num);

      for (size_t i = 1; i < segment_num; i++)
      {
         h_cur = points[i].get_x() - points[i - 1].get_x();
         h_next = points[i + 1].get_x() - points[i].get_x();

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
      for (size_t i = segment_num - 3; i != SIZE_MAX; i--)
         c[i] = (c[i] - c[i + 1] * d[i]) / b[i];

      c[segment_num] = 0.0;
      for (size_t i = segment_num - 1; i > 0; i--)
         c[i] = c[i - 1];
      c[0] = 0.0;

      for (size_t i = 0; i < segment_num; i++)
      {
         h_cur = points[i + 1].get_x() - points[i].get_x();
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
            result[0] = a[i] + b[i] * diff + c[i] * pow(diff, 2) + d[i] * pow(diff, 3);      // value
            result[1] = b[i] + 2.0 * c[i] * diff + 3.0 * d[i] * pow(diff, 2);                // first derivative
            result[2] = 2.0 * c[i] + 6.0 * d[i] * diff;                                      // second derivative
            return result;
         }

      throw std::runtime_error("The point wasn't found");
   }

   std::vector<double> CIS::regular(double a, double b, size_t n)
   {
      std::vector<double> result;
      points.clear();
      double h = fabs(b - a) / (n * 1.0), x = 0.0;
      for (size_t i = 0; i <= n; i++)
      {
         x = a + i * h;
         points.push_back(Point(x, 0, 0));
         result.push_back(sin(x));         // you can change function here
      }
      return result;
   }

   std::vector<double> CIS::adaptive(double a, double b, double r, size_t n)
   {
      points.clear();
      double h = 1.0, len = fabs(b - a), x = 0.0;
      for (size_t i = 1; i < n; i++)
         h = h + pow(r, i);
      h = len / h;
      std::vector<double> result;
      result[0] = a;
      for (size_t i = 1; i <= n; i++)
      {
         x = points[i - 1].get_x() + h * pow(r, i - 1);
         points.push_back(Point(x, 0, 0));
         result.push_back(x);             // you can change function here
      }
      return result;
   }
}