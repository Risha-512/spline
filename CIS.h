#pragma once

#include "Spline.h"

namespace Spline
{
    class CIS : public Spline
    {
    private:
        std::vector<Point> points;
        std::vector<double> a, b, c, d;
    public:
        void update_spline(const std::vector<Point>& Points, const std::vector<double>& F_value) override;
        std::vector<double> get_value(const Point& p) const override;
    };
}