#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <tuple>

typedef std::vector<double> vector;
typedef std::vector<std::complex<double>> cvector;

typedef std::complex<double>(*function)(double x);

std::complex<double> y(double x)
{
	using namespace std::complex_literals;

	return -1.0 * pow(M_E, (-1. - 1i) * x);
}

std::tuple<vector, cvector> matrix_init(int N, double h)
{
	using namespace std::complex_literals;

	vector a(N - 1, 1); cvector b(N, -2. - h * h * 2i);

	return std::make_tuple(a, b);
}

cvector NewtonMethod(int grid_start, int grid_end, int N, double h)
{
	vector x(N + 2);

	x.at(0) = grid_start;

	for (auto i = x.begin() + 1; i < x.end(); i++)
		*i = *(i - 1) + h;

	cvector u(N), b; vector a;

	std::tie(a, b) = matrix_init(N, h);

	cvector alpha(N), beta(N);

	alpha.at(1) = a.at(0) / b.at(0);
	beta.at(1) = y(x.at(0)) / b.at(0);

	for (auto i = 1; i < N - 1; i++)
	{
		alpha.at(i + 1) = a.at(i - 1) / (b.at(i) - a.at(i - 1) * alpha.at(i));
		beta.at(i + 1) = (0. + a.at(i - 1) * beta.at(i)) / (b.at(i) - a.at(i - 1) * alpha.at(i));
	}

	u.at(N - 1) = (y(x.at(N + 1)) + a.at(N - 2) * beta.at(N - 1)) / (b.at(N - 1) - a.at(N - 2) * alpha.at(N - 1));

	for (auto i = N - 2; i > -1; i--)
		u.at(i) = alpha.at(i + 1) * u.at(i + 1) + beta.at(i + 1);

	return u;
}

int main()
{
	long int grid_start = 0, grid_end = 1, N = 3;
	double h = 1. / 4.;

	std::string goon = "y";

	while (goon == "y")
	{
		cvector u = NewtonMethod(grid_start, grid_end, N, h);
		for (auto i = u.begin(); i < u.end(); i++)
			std::cout << *i << '\n';

		double local_h = h;

		for (auto i = u.begin(); i < u.end(); i++)
		{
			std::cout << "diff: " << y(local_h) - *i << '\n';
			local_h += h;
		}

		std::cout << '\n' << "Continue(y/n)?: ";
		std::cin >> goon;

		N *= 2;
		h /= 2;
	}
}