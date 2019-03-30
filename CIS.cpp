#include "CIS.h"
#include <iostream>
#include <math.h>

namespace Spline
{
   void CIS::update_spline(const std::vector<Point>& P, const std::vector<double> &func_value)
   {
      this->points.clear();
      for (auto elem : P)
         this->points.push_back(elem);

      size_t segment_num = P.size() - 1;
      double h_cur, h_next;

      A.resize(segment_num);
      B.resize(segment_num);
      C.resize(segment_num + 1);
      D.resize(segment_num);

      for (size_t i = 1; i < segment_num; i++)
      {
         h_cur = P[i].get_x() - P[i - 1].get_x();
         h_next = P[i + 1].get_x() - P[i].get_x();

         A[i] = h_cur;
         B[i - 1] = 2 * (h_cur + h_next);
         C[i - 1] = 3.0 * ((func_value[i + 1] - func_value[i]) / h_next - (func_value[i] - func_value[i - 1]) / h_cur);
         D[i - 1] = h_next;
      }

      for (size_t i = 1; i < segment_num - 1; i++)
      {
         B[i] -= A[i] / B[i - 1] * D[i - 1];
         C[i] -= A[i] / B[i - 1] * C[i - 1];
      }

      C[segment_num - 1] /= B[segment_num - 2];
      for (size_t i = segment_num - 3; i >= 0; i--)
         C[i] = (C[i] - C[i + 1] * D[i]) / B[i];

      C[segment_num] = 0.0;
      for (size_t i = segment_num - 1; i > 0; i--)
         C[i] = C[i - 1];
      C[0] = 0.0;

      for (size_t i = 0; i < segment_num; i++)
      {
         h_cur = P[i + 1].get_x() - P[i].get_x();
         A[i] = func_value[i];
         B[i] = (func_value[i + 1] - func_value[i]) / h_cur - (C[i + 1] + 2.0 * C[i]) * h_cur / 3.0;
         D[i] = (C[i + 1] - C[i]) / h_cur / 3.0;
      }
   }

   void CIS::get_value(const Point &P, double *result) const
   {
      double eps = 1e-7;
      size_t segment_num = points.size() - 1;

      for (size_t i = 0; i < segment_num; i++)
         if (P.get_x() > points[i].get_x() && P.get_x() < points[i + 1].get_x() || fabs(P.get_x() - points[i].get_x()) < eps ||
            fabs(P.get_x() - points[i + 1].get_x()) < eps)
         {
            double diff = fabs(P.get_x() - points[i].get_x());
            result[0] = A[i] + B[i] * diff + C[i] * pow(diff, 2) + D[i] * pow(diff, 3);
            result[1] = B[i] + 2.0 * C[i] * diff + 3.0 * D[i] * pow(diff, 2);
            result[2] = 2.0 * C[i] + 6.0 * D[i] * diff;
            return;
         }

      throw std::exception("The point wasn't found");
   }
}