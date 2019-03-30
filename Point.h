#pragma once
namespace Spline
{
   class Point
   {
   private:
      double X, Y, Z;
   public:
      Point(double x, double y, double z) : X(x), Y(y), Z(z) {}

      double get_x() const;
      double get_y() const;
      double get_z() const;
   };
}