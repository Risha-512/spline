#pragma once
namespace Spline
{
   class Point
   {
   private:
      double x, y, z;
   public:
      Point(double x, double y, double z) : x(x), y(y), z(z) {}

      double get_x() const;
      double get_y() const;
      double get_z() const;
   };
}