#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

double K(double x, double t)
{
	return sin(t) + t * cos(x);
}

double u(double x)
{
	return -1. * (pow(M_PI, 2) * cos(x)) / 18 + 1 - (2 * x) / M_PI;
}

double f(double x)
{
	return 1 - (2 * x) / M_PI;
}

double get_ksi(double a, double b, double x)
{
	return (a + b + (b - a) * x) / 2;
}

double get_w(double ksi)
{
	return 2 / ((1 - pow(ksi, 2)) * pow((15 * pow(ksi, 2) - 3) / 2, 2));
}

std::vector<double> ksi_init(int n, double h, int N, double a, std::vector<double> x)
{
	std::vector<double> vec;
	double b = h;

	int j = 0;
	for (auto i = 0; i < n * N; i++)
	{
		vec.push_back(get_ksi(a, b, x.at(j)));
		
		if ((i + 1) % n == 0)
		{
			a += h; b += h;
		}

		j++;
		if (j == n)
			j = 0;
	}

	return vec;
}

std::vector<double> w_init(int n, int N, std::vector<double> x)
{
	std::vector<double> vec;

	int j = 0;
	for (auto i = 0; i < n * N; i++)
	{
		vec.push_back(get_w(x.at(j)));

		j++;
		if (j == n)
			j = 0;
	}

	return vec;
}

std::vector<double> f_init(int n, int N, std::vector<double> ksi)
{
	std::vector<double> vec;

	for (auto i = 0; i < n * N; i++)
		vec.push_back(f(ksi.at(i)));

	return vec;
}

std::vector<double> operator * (double** matr, std::vector<double> vec)
{
	std::vector<double> res(vec.size());

	for (auto i = 0; i < vec.size(); i++)
	{
		res.at(i) = 0;

		for (auto j = 0; j < vec.size(); j++)
			res.at(i) += matr[i][j] * vec.at(j);
	}

	return res;
}

double** matrix_init(int n, double h, int N, std::vector<double> ksi, std::vector<double> w)
{
	int size = n * N;
	double c = h / 2;

	double** matrix = new double* [size];
	for (auto i = 0; i < size; i++)
	{
		matrix[i] = new double[size];

		for (auto j = 0; j < size; j++)
		{
			if (i == j)
				matrix[i][j] = (1 - c * w.at(j) * K(ksi.at(i), ksi.at(j)));
			else
				matrix[i][j] = -1. * (c * w.at(j) * K(ksi.at(i), ksi.at(j)));
		}
	}

	return matrix;
}

std::vector<double> Gauss(double** A, std::vector<double> b)
{
	int n = b.size();
	int k = 0, index;
	double max;

	std::vector<double> x(n);

	while (k < n)
	{
		max = abs(A[k][k]);
		index = k;

		for (auto i = k + 1; i < n; i++)
			if (abs(A[i][k]) > max)
			{
				max = abs(A[i][k]);
				index = i;
			}

		if (max < DBL_EPSILON)
			throw "max is 0";

		for (auto i = 0; i < n; i++)
		{
			double tmp = A[k][i];
			A[k][i] = A[index][i];
			A[index][i] = tmp;
		}

		double tmp = b.at(k);
		b.at(k) = b.at(index);
		b.at(index) = tmp;

		for (auto i = k; i < n; i++)
		{
			double tmp = A[i][k];

			if (abs(tmp) < DBL_EPSILON)
				continue;

			for (auto j = 0; j < n; j++)
				A[i][j] = A[i][j] / tmp;

			b.at(i) = b.at(i) / tmp;

			if (i == k)
				continue;

			for (auto j = 0; j < n; j++)
				A[i][j] = A[i][j] - A[k][j];

			b.at(i) = b.at(i) - b.at(k);
		}

		k++;
	}

	for (k = n - 1; k >= 0; k--)
	{
		x.at(k) = b.at(k);

		for (auto i = 0; i < k; i++)
			b.at(i) = b.at(i) - A[i][k] * x.at(k);
	}

	return x;
}

int main()
{
	const double a = 0, b = M_PI;
	const int n = 3, accuracy_degree = 2 * n - 1;

	double h = (b - a);

	std::vector<double> x = { -sqrt(3. / 5.), 0, sqrt(3. / 5.) };

	std::string goon = "y";

	while (goon == "y")
	{
		int N = (b - a) / h;

		std::vector<double> ksi = ksi_init(n, h, N, a, x);

		std::vector<double> w = w_init(n, N, x);


		double** A = matrix_init(n, h, N, ksi, w);

		/*for (auto i = 0; i < n * N; i++)
		{
			for (auto j = 0; j < n * N; j++)
				std::cout << A[i][j] << "   ";

			std::cout << '\n';
		}*/
		std::cout << '\n';

		std::vector<double> c = f_init(n, N, ksi);

		std::vector<double> u_appr = Gauss(A, c);

		for (auto i = 0; i < n * N; i++)
			std::cout << fabs(u(ksi.at(i)) - u_appr.at(i)) << '\n';

		std::cout << '\n' << "Continue(y/n)?: ";
		std::cin >> goon;

		h /= 2;
	}

	
}