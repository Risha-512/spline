#include "CIS.h"
#include "SS.h"
#include <iostream>

using namespace Spline;

int main()
{
   //parameters of cubic interpolation spline

   double a = 0.0, b = 1.0;
   size_t n = 10;
   CIS cspl;
   std::vector<double> value = cspl.regular(a, b, n);     // function value in given points
   cspl.update(value);

   n = 15;
   double h = fabs(b - a) / (n * 1.0), x = 0.0;
   std::vector<std::vector<double>> result (n);

   std::cout << "Cubic Interpolation Spline:" << std::endl << "a = " << a << ", b = " << b << ", n = " << n << std::endl << std::endl;
   for (size_t i = 0; i < n; i++)
   {
      x = a + i * h;
      result[i] = cspl.get_value(Point(x, 0.0, 0.0));
      std::cout << " " << result[i][0] << "\t" << result[i][1] << "\t" << result[i][2] << std::endl;      // make a graph of values result[i][0]
   }

   /****************************************************************************************************************************************************/

   // parameters of smoothing spline

   double smooth = 0.1;
   a = 1.0; b = 2.0; n = 10;
   SS sspl(smooth);
   value = sspl.regular(a, b, n);
   sspl.update(value);

   n = 15;
   h = fabs(b - a) / (n * 1.0), x = 0.0;
   result.clear();
   result.resize(n);

   std::cout << std::endl << "Smoothing Spline:" << std::endl << "a = " << a << ", b = " << b << ", n = " << n << std::endl << std::endl;
   for (size_t i = 0; i < n; i++)
   {
      x = a + i * h;
      result[i] = sspl.get_value(Point(x, 0.0, 0.0));
      std::cout << " " << result[i][0] << "\t" << result[i][1] << "\t" << result[i][2] << std::endl;      // make a graph of values result[i][0]
   }

   return 1;
}