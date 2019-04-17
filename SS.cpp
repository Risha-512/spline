#include "SS.h"
#include "functional"

namespace Spline
{
    void SS::master_element(size_t segment_num, const double& x, double& ksi) const
    {
        ksi = 2.0 * (x - points[segment_num].get_x()) /
              (points[segment_num + 1].get_x() - points[segment_num].get_x()) - 1.0;
    }
    
    double SS::basic(char num, const double& ksi) const
    {
        switch (num)
        {
            case 1:
                return 0.5 * (1 - ksi);
            case 2:
                return 0.5 * (1 + ksi);
            default:
                throw std::runtime_error("Wrong function number");
        }
    }
    
    double SS::der_basic(char num, const double& ksi) const
    {
        switch (num)
        {
            case 1:
                return -0.5;
            case 2:
                return 0.5;
            default:
                throw std::runtime_error("Wrong derivative number");
        }
    }
    
    std::vector<double> SS::get_value(const Point& p) const
    {
        double eps = 1e-7;
        size_t segment_num = points.size() - 1;
        double elem = p.get_x();
        std::vector<double> result(3, 0);
        
        for (size_t i = 0; i < segment_num; i++)
            if (elem > points[i].get_x() && elem < points[i + 1].get_x() || fabs(elem - points[i].get_x()) < eps ||
                fabs(elem - points[i + 1].get_x()) < eps)
            {
                double h = points[i + 1].get_x() - points[i].get_x(), ksi;
                master_element(i, elem, ksi);
                result[0] = alpha[i] * basic(1, ksi) + alpha[i + 1] * basic(2, ksi);                         // value
                result[1] = (alpha[i] * der_basic(1, ksi) + alpha[i + 1] * der_basic(2, ksi)) * 2.0 /
                            h;     // first derivative
                result[2] = 0.0;                                                                             // second derivative
                return result;
            }
        throw std::runtime_error("The point wasn't found");
    }
    
    void SS::update_spline(const std::vector<Point>& Points, const std::vector<double>& F_value)
    {
        if (Points.empty())
            throw std::runtime_error("Vector of points is empty");
        
        points.clear();
        points = Points;
        
        size_t segment_num = points.size() - 1;
        alpha.resize(segment_num + 1);
        std::vector<double> a, b, c;
        a.resize(segment_num + 1);
        b.resize(segment_num + 1);
        c.resize(segment_num + 1);
        
        auto assembling = [ & ](size_t i, const Point& p, const double& value, const double& weight)
        {
            double elem = p.get_x(), ksi;
            master_element(i, elem, ksi);
            
            double first = basic(1, ksi), second = basic(2, ksi);
            b[i] += weight * first * first;
            b[i + 1] += weight * second * second;
            a[i + 1] += weight * first * second;
            c[i] += weight * second * first;
            alpha[i] += weight * first * value;
            alpha[i + 1] += weight * second * value;
        };
        
        for (size_t i = 0; i < segment_num; i++)
        {
            assembling(i, points[i], F_value[i], 1.0);
            double h = points[i + 1].get_x() - points[i].get_x();
            b[i] += 4.0 / h * smooth;
            b[i + 1] += 4.0 / h * smooth;
            a[i + 1] -= 4.0 / h * smooth;
            c[i] -= 4.0 / h * smooth;
        }
        
        assembling(segment_num - 1, points[segment_num], F_value[segment_num], 1.0);
        
        for (size_t j = 1; j < segment_num; j++)
        {
            b[j] -= a[j] / b[j - 1] * c[j - 1];
            alpha[j] -= a[j] / b[j - 1] * alpha[j - 1];
        }
        
        alpha[segment_num] /= b[segment_num];
        for (size_t j = segment_num - 1; j != SIZE_MAX; j--)
            alpha[j] = (alpha[j] - alpha[j + 1] * c[j]) / b[j];
        
    }
}
