#include "CIS.h"
#include "SS.h"

namespace Spline
{

	//std::vector <Point> regular(double a, double b, size_t n)
	//{
	//	//Value.clear();
	//	double h = fabs(b - a) / (n * 1.0);
	//	std::vector<Point> result;
	//	double x = 0.0;
	//	for (size_t i = 0; i <= n; i++)
	//	{
	//		x = a + i * h;
	//		result.push_back(Point(x, 0, 0));
	//		//Value.push_back(x);
	//	}
	//	return result;
	//}

	//std::vector<Point> adaptive(double a, double b, double r, size_t n)
	//{
	//	double h = 1.0, len = fabs(b - a);
	//	for (size_t i = 1; i < n; i++)
	//		h = h + pow(r, i);
	//	h = len / h;
	//	std::vector<Point> result;
	//	result[0] = Point(a, 0, 0);
	//	for (size_t i = 1; i <= n; i++)
	//		result.push_back(Point(result[i - 1].get_x() + h * pow(r, i - 1), 0, 0));
	//	return result;
	//}
}

using namespace Spline;

int main()
{
	std::vector <double> value;
	double a = 0.0, b = 1.0;
	size_t n = 10;
	double h = fabs(b - a) / (n * 1.0);
	std::vector<Point> result;
	double x = 0.0;
	for (size_t i = 0; i <= n; i++)
	{
		x = a + i * h;
		result.push_back(Point(x, 0, 0));
		value.push_back(x);
	}
	SS g(0.01);
	g.update(result, value);
	std::vector<double> Ans;
	n = 100;
	h = fabs(b - a) / (n * 1.0);
	for (size_t i = 0; i <= n; i++)
	{
		x = a + i * h;
		result.push_back(Point(x, 0, 0));
		Ans = g.get_value(result[i]);
	}


	//std::vector <double> value;
	//double a = 0.0, b = 1.0;
	//size_t n = 10;
	//double h = fabs(b - a) / (n * 1.0);
	//std::vector<Point> result;
	//double x = 0.0;
	//for (size_t i = 0; i <= n; i++)
	//{
	//	x = a + i * h;
	//	result.push_back(Point(x, 0, 0));
	//	value.push_back(x * x);
	//}
	//CIS S3;
	//S3.update(result, value);
	//std::vector<double> Ans;
	//n = 100;
	//h = fabs(b - a) / (n * 1.0);
	//for (size_t i = 0; i <= n; i++)
	//{
	//	x = a + i * h;
	//	result.push_back(Point(x, 0, 0));
	//	Ans = S3.get_value(result[i]);
	//}
    return 1;
}