#include "CIS.h"
#include "SS.h"
#include "split.h"
#include <iostream>
#include <iomanip>

using namespace Spline;

int main()
{
   // set console output parameters
   std::cout.setf(std::ios::fixed, std::ios::floatfield);
   std::cout.precision(6);
   
   // function can be changed here
   auto function = [](double x){
       return x*x*x;
   };
   
   // parameters of cubic interpolation spline
   double a = 0.0, b = 1.0;
   size_t n = 10;
   CIS cspl;
   
   std::vector<Point> points_vec;
   std::vector<double> value;
   regular(points_vec, value, a, b, n, function);
   
   cspl.update_spline(points_vec, value);

   n = 15;
   double h = fabs(b - a) / (double)n, x = 0.0;
   std::vector<std::vector<double>> result(n);

   std::cout << "Cubic Interpolation Spline:" << std::endl
   << "a = " << a << ", b = " << b << ", n = " << n << std::endl << std::endl;
   for (size_t i = 0; i < n; i++)
   {
      x = a + i * h;
      result[i] = cspl.get_value(Point(x, 0.0, 0.0));

      for (size_t j = 0; j < 3; j++) // make a graph of values result[i][0]
      {
          if (result[i][j] >= 0) // minus takes one symbol, so if positive add space
              std::cout << ' ';
          std::cout << result[i][j] << '\t';
      }
      std::cout << std::endl;
   }

   /****************************************************************************************************************************************************/

   // parameters of smoothing spline

   double smooth = 0.1;
   a = 1.0; b = 2.0; n = 10;
   
   SS sspl(smooth);
   
   regular(points_vec, value, a, b, n, function);
   sspl.update_spline(points_vec, value);

   n = 15;
   h = fabs(b - a) / (double)n, x = 0.0;
   result.clear();
   result.resize(n);

   std::cout << std::endl << "Smoothing Spline(" << smooth << "):" << std::endl
   << "a = " << a << ", b = " << b << ", n = " << n << std::endl << std::endl;
   for (size_t i = 0; i < n; i++)
   {
      x = a + i * h;
      result[i] = sspl.get_value(Point(x, 0.0, 0.0));
      
      for (size_t j = 0; j < 3; j++) // make a graph of values result[i][0]
      {
          if (result[i][j] >= 0) // minus takes one symbol, so if positive add space
              std::cout << ' ';
          std::cout << result[i][j] << '\t';
      }
      std::cout << std::endl;
   }

   return 1;
}