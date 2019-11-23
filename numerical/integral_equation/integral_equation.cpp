#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>

double K(double x, double t)
{
	return sin(t) + t * cos(x);
}

double u(double x)
{
	return pow(M_PI, 4) / 36 - (pow(M_PI, 2) * cos(x)) / 18 + 1 - (2 * x) / M_PI;
}

double f(double x)
{
	return 1 - (2 * x) / M_PI;
}

double x(double a, double b, double ksi)
{
	return (a + b + (b - a) * ksi) / 2;
}

double w(double x)
{
	return 2 / ((1 - pow(x, 2)) * pow((15 * pow(x, 2) - 3) / 2, 2));
}

std::vector<double> x_init(int n, double a, double b, std::vector<double> ksi)
{
	std::vector<double> vec;

	for (auto i = 0; i < n; i++)
		vec.push_back(x(a, b, ksi.at(i)));

	return vec;
}

std::vector<double> w_init(int n, std::vector<double> x)
{
	std::vector<double> vec;

	for (auto i = 0; i < n; i++)
		vec.push_back(w(x.at(i)));

	return vec;
}

int main()
{
	const double a = 0, b = M_PI;
	const int n = 3, accuracy_degree = 2 * n - 1;

	std::vector<double> ksi = { -sqrt(15) / 5, 0, sqrt(15) / 5 };

	std::vector<double> x = x_init(n, a, b, ksi);

	std::vector<double> w = w_init(n, x);

	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < n; j++)
		{
			std::cout << "For x" << i << " and x" << j << " K=" << K(x.at(i), x.at(j)) << '\n';
		}
	}

	std::cout << u(1);
}
