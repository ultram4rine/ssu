#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <tuple>

typedef std::vector<double> vector;
typedef std::vector<std::complex<double>> cvector;

std::complex<double> y(double x)
{
	using namespace std::complex_literals;

	return -1.0 * pow(M_E, (-1.0 - 1i) * x);
}

cvector F_init(double h, int N)
{
	using namespace std::complex_literals;
	
	cvector F;
	F.resize(N);
	F.at(0) = y(0);
	F.at(N - 1) = y(N);

	double param = h;

	for (auto i = 1; i < N - 1; i++)
	{
		F.at(i) = param * param * 2.0 * 1i * y(param);
		param += h;
	}

	return F;
}

std::tuple<vector, vector, vector> matrix_init(double h, int N)
{
	double h_inv = pow(h, -1);
	vector a, b, c;

	a.resize(N - 1), b.resize(N), c.resize(N - 1);

	a.at(N - 2) = 0;
	b.at(0) = 1;
	b.at(N - 1) = 1;
	c.at(0) = 0;

	for (auto i = 1; i < N - 1; i++)
	{
		a.at(i - 1) = -1 * h_inv * h_inv;
		b.at(i) = 2 * h_inv * h_inv;
		c.at(N - i - 1) = a.at(i - 1);
	}

	return std::make_tuple(a, b, c);
}

cvector ThomasALG(double h, int N)
{
	double h_inv = pow(h, -1);
	vector a, b, c;

	tie(a, b, c) = matrix_init(h, N);
	cvector d = F_init(h, N);

	cvector P, Q;
	P.resize(N), Q.resize(N);

	P.at(1) = -1.0*c.at(0) / b.at(0);
	Q.at(1) = d.at(0) / b.at(0);

	for (auto i = 2; i < N - 2; i++)
	{
		P.at(i + 1) = (-1.0 * c.at(i)) / (a.at(i - 1) * P.at(i) + b.at(i));
		Q.at(i + 1) = (d.at(i) - a.at(i - 1) * Q.at(i - 1)) / (a.at(i - 1) * P.at(i) + b.at(i));
	}

	cvector x;
	x.resize(N);
	x.at(N - 1) = (d.at(N - 1) - a.at(N - 2) * Q.at(N - 1)) / (a.at(N - 2) * P.at(N - 1) + b.at(N - 1));

	for (auto i = N - 2; i > -1; i--)
	{
		x.at(i) = P.at(i + 1) * x.at(i + 1) + Q.at(i + 1);
	}

	return x;
}

int main()
{
	int N = 10;
	double h = 0.1;

	std::string goon = "y";

	while (goon == "y")
	{
		cvector x = ThomasALG(h, N);
		for (auto i = 0; i < N; i++)
		{
			std::cout << x.at(i) << '\n';
		}

		double local_h = 0;

		for (auto i = 0; i < N; i++)
		{
			std::cout << "diff: " << abs(y(local_h) - x.at(i)) << '\n';
			local_h += h;
		}

		std::cout << '\n' << "Continue(y/n)?: ";
		std::cin >> goon;

		h /= 2;
	}
}
