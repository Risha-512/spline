#pragma once

namespace Spline
{
   class Point
   {
   private:
      double x, y, z;
   public:
      Point(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
	  Point() : x(0), y(0), z(0) {}
      double get_x() const;
      double get_y() const;
      double get_z() const;
   };
}