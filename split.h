#include "Spline.h"

namespace Spline
{
    template <typename Func>
    void regular(std::vector<Point> &points, std::vector<double> &F_value, double a, double b, size_t n, Func f)
    {
        points.clear();
        F_value.clear();
        
        double h = fabs(b - a) / (double)n, x = 0.0;
        for (size_t i = 0; i <= n; i++)
        {
            x = a + i * h;
            points.emplace_back(Point(x, 0, 0));
            F_value.push_back(f(x));
        }
    }
    
    template <typename Func>
    void addaptive(std::vector<Point> &points, std::vector<double> &F_value, double a, double b, double r, size_t n, Func f)
    {
        points.clear();
        F_value.clear();
        
        double h = 1.0, len = fabs(b - a), x = 0.0;
        for (size_t i = 1; i < n; i++)
            h = h + pow(r, i);
        h = len / h;
        F_value[0] = a;
        for (size_t i = 1; i <= n; i++)
        {
            x = points[i - 1].get_x() + h * pow(r, i - 1);
            points.emplace_back(Point(x, 0, 0));
            F_value.push_back(f(x));
        }
    }
}
