#pragma once

#include "Point.h"
#include <vector>
#include <cmath>
#include <stdexcept>

namespace Spline
{
    class Spline
    {
    public:
        virtual void update_spline(const std::vector<Point>& Points, const std::vector<double>& F_value) = 0;
        virtual std::vector<double> get_value(const Point& p) const = 0;
    };
}