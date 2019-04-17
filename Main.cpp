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
    auto function = [](double x) { return x*x; };
    
    // parameters
    size_t n_nodes = 25,
            n_values = 30;
    double a = 0.0, b = 1.0;
    double h = fabs(b - a) / (double) n_values,
            x = 0.0;
    double max_apr_err = 0.0;
    
    std::vector<Point> points_vec;
    std::vector<double> value;
    
    // two-dimensional vector for storing result
    std::vector<std::vector<double>> result(n_values);
    
    // print out parameters
    std::cout << "a = " << a
              << ", b = " << b
              << ", n = " << n_values
              << ", h = " << h
              << std::endl << std::endl;
    //
    // Cubic Interpolation Spline
    //
    CIS cspl;
    
    //    addaptive(points_vec, value, a, b, 0.5, n_nodes, function);
    regular(points_vec, value, a, b, n_nodes, function);
    cspl.update_spline(points_vec, value);
    
    std::cout << "Cubic Interpolation Spline:" << std::endl;
    for (size_t i = 0; i < n_values; i++)
    {
        x = a + i * h;
        result[i] = cspl.get_value(Point(x, 0.0, 0.0));
        
        if (double approximation_error = fabs(2*x - result[i][1]); approximation_error > max_apr_err)
            max_apr_err = approximation_error;
        
        for (size_t j = 0; j < 3; j++)
        {
            if (result[i][j] >= 0) // minus takes one symbol, so if positive add space
                std::cout << ' ';
            std::cout << result[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    
    std::cout << "max approximation error: " << max_apr_err << std::endl;
    
    //
    // Smoothing Spline
    //
    
    double smooth = 0.1;
    SS sspl(smooth);
    
    regular(points_vec, value, a, b, n_nodes, function);
    sspl.update_spline(points_vec, value);
    
    result.clear();
    result.resize(n_values);
    
    std::cout << std::endl << "Smoothing Spline(" << smooth << "):" << std::endl;
    for (size_t i = 0; i < n_values; i++)
    {
        x = a + i * h;
        result[i] = sspl.get_value(Point(x, 0.0, 0.0));
        
        for (size_t j = 0; j < 3; j++)
        {
            if (result[i][j] >= 0) // minus takes one symbol, so if positive add space
                std::cout << ' ';
            std::cout << result[i][j] << '\t';
        }
        std::cout << std::endl;
    }
    
    return 1;
}
