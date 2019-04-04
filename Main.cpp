#include "CIS.h"
#include "SS.h"

namespace Spline
{
	std::vector <double> regular(double a, double b, size_t n)
	{
		double h = fabs(b - a) / n;
		std::vector<double> result(n + 1);
		for (size_t i = 0; i <= n; i++)
			result[i] = a + i * h;
		return result;
	}

	std::vector<double> adaptive(double a, double b, double r, size_t n)
	{
		double h = 1.0, len = fabs(b - a);
		for (size_t i = 1; i < n; i++)
			h = h + pow(r, i);
		h = len / h;
		std::vector<double> result(n + 1);
		result[0] = a;
		for (size_t i = 1; i <= n; i++)
			result[i] = result[i - 1] + h * pow(r, i - 1);
		return result;
	}
}

using namespace Spline;

int main()
{
    CIS cis;
    double a = 0.0, b = 12.0;
    size_t n = 6;
    std::vector<double> test = regular(a, b, n);
    std::vector<std::vector<double>> spline_matrix;



    //for (const auto &elem : test)
    //{
    //	spline_matrix.push_back(cis.get_value(elem));
    //}
    //std::vector<Point> test = adaptive(0, 15, 2, 4);
    //test.clear();
    //test = regular(0, 10, 5);
    return 1;
}