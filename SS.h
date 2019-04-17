#pragma once

#include "Spline.h"

namespace Spline
{
    class SS : public Spline
    {
    private:
        double smooth;
        std::vector<Point> points;
        std::vector<double> alpha;
        
        void master_element(size_t segment_num, const double& x, double& ksi) const;
        double basic(char num, const double& ksi) const;
        double der_basic(char num, const double& ksi) const;
    public:
        SS(const double& s) : smooth(s)
        {};
        void update_spline(const std::vector<Point>& Points, const std::vector<double>& F_value) override;
        
        std::vector<double> get_value(const Point& p) const override;
    };
}
