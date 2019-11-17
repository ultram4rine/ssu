#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <complex>
#include <tuple>

typedef std::complex<double> complex;
typedef std::vector<double> vector;
typedef std::vector<std::complex<double>> cvector;

typedef std::complex<double>(*function)(double x);

std::complex<double> y(double x)
{
	using namespace std::complex_literals;

	return -1.0 * pow(M_E, (-1. - 1i) * x);
}

cvector f_init(int N, int n)
{
	cvector f(n, 0);

	f.at(0) = y(0);
	f.at(n - 1) = y(N);

	return f;
}

std::tuple<vector, cvector, vector> matrix_init(int N, double h)
{
	using namespace std::complex_literals;

	vector a(N / h, 1); cvector c(N / h, -2. - h * h * 2i); vector b(N / h, 1);

	a.at(0) = 0;
	b.at(N / h - 1) = 0;

	return std::make_tuple(a, c, b);
}

cvector ThomasAlg(int N, double h)
{
	complex m;

	vector a, b; cvector c;

	std::tie(a, c, b) = matrix_init(N, h);

	int n = N / h;

	cvector f = f_init(N, n);

	for (int i = 1; i < n; i++)
	{
		m = a.at(i) / c.at(i - 1);
		c.at(i) = c.at(i) - m * b.at(i - 1);
		f.at(i) = f.at(i) - m * f.at(i - 1);
	}

	cvector u(n);

	u.at(n - 1) = f.at(n - 1) / c.at(n - 1);

	for (int i = n - 2; i >= 0; i--)
	{
		u.at(i) = (f.at(i) - b.at(i) * u.at(i + 1)) / c.at(i);
	}

	return u;
}

int main()
{
	int k = 0;

	long int N = 1;
	double h = 1. / 4., error, prev_error;

	std::string goon = "y";

	while (goon == "y")
	{
		cvector u = ThomasAlg(N, h);

		/*for (auto local_h = h; local_h <= N; local_h += h)
			std::cout << y(local_h) << '\n';

		std::cout << '\n';

		for (auto i = u.begin(); i < u.end(); i++)
			std::cout << *i << '\n';

		std::cout << '\n';*/

		double local_h = h;

		error = abs(y(local_h)) - abs(u.at(0));

		for (auto i = u.begin(); i < u.end(); i++)
		{
			abs(y(local_h)) - abs(*i) > error ? error = abs(y(local_h)) - abs(*i) : error;

			//std::cout << "diff at " << h << ": " << abs(y(local_h)) - abs(*i) << '\n';
			local_h += h;
		}

		std::cout << '\n' << error << '\n' << '\n';

		if (k != 0)
			std::cout << "Expected error ratio: " << 4 << '\n' << std::setprecision(10)
			<< "Actual error ratio: " << prev_error / error << '\n' << '\n';

		std::cout << '\n' << "Continue(y/n)?: ";
		std::cin >> goon;

		k++;

		h /= 2;

		prev_error = error;
	}
}