#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <tuple>

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

double get_w(double x)
{
	return 2 / ((1 - pow(x, 2)) * pow((15 * pow(x, 2) - 3) / 2, 2));
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

std::tuple<double**, std::vector<double>> init(int n, double h, int N, double a, std::vector<double> x)
{
	int size = n * N, k = 0, l = 0;
	double c = h / 2, ksi_i, ksi_j;

	double a_i = a, a_j = a, b_i = h, b_j = h;

	std::vector<double> free_members;

	double** matrix = new double* [size];
	for (auto i = 0; i < size; i++)
	{
		matrix[i] = new double[size];

		ksi_i = get_ksi(a_i, b_i, x.at(k));

		for (auto j = 0; j < size; j++)
		{
			ksi_j = get_ksi(a_j, b_j, x.at(l));

			if (i == j)
				matrix[i][j] = (1 - c * get_w(x.at(l)) * K(ksi_i, ksi_j));
			else
				matrix[i][j] = -1. * (c * get_w(x.at(l)) * K(ksi_i, ksi_j));

			l++;
			if (l == n)
			{
				l = 0;
				a_j += h;
				b_j += h;
			}
		}

		free_members.push_back(f(ksi_i));

		k++;
		if (k == n)
		{
			k = 0;
			a_i += h;
			b_i += h;
		}
	}

	return std::make_tuple(matrix, free_members);
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
	int k = 0;
	const double a = 0, b = M_PI;
	const int n = 3, accuracy_degree = 2 * n - 1;

	double h = (b - a), error, prev_error;

	std::vector<double> x = { -sqrt(3. / 5.), 0, sqrt(3. / 5.) };

	std::string goon = "y";

	while (goon == "y")
	{
		int N = (b - a) / h;
		std::cout << "N = " << N << '\n';
		std::cout << "Size = " << n * N << '\n';

		std::vector<double> ksi = ksi_init(n, h, N, a, x);

		double** A;
		std::vector<double> c;

		std::tie(A, c) = init(n, h, N, a, x);

		/*for (auto i = 0; i < n * N; i++)
		{
			for (auto j = 0; j < n * N; j++)
				std::cout << A[i][j] << "   ";

			std::cout << '\n';
		}*/

		std::vector<double> u_appr = Gauss(A, c);

		/*for (auto i = 0; i < n * N; i++)
			std::cout << u(ksi.at(i)) << "  ~  " << u_appr.at(i) <<'\n';*/

		error = fabs(u(ksi.at(0)) - u_appr.at(0));

		for (auto i = 0; i < n * N; i++)
			fabs(u(ksi.at(i)) - u_appr.at(i)) > error ? error = fabs(u(ksi.at(i)) - u_appr.at(i)) : error;

		std::cout << '\n' << error << '\n' << '\n';

		if (k != 0)
			std::cout << "Expected error ratio: " << 64 << '\n' << std::setprecision(10)
			<< "Actual error ratio: " << prev_error / error << '\n' << '\n';

		std::cout << '\n' << "Continue(y/n)?: ";
		std::cin >> goon;
		std::cout << '\n';

		k++;

		h /= 2;

		prev_error = error;
	}
}