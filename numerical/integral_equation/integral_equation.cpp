#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <tuple>

int sign(double x)
{
	return x < 0 ? -1 : 1;
}

double sum(vector x)
{
	double sum = 0;
	for (auto i = 0; i < x.size(); i++)
		sum += x.at(i);
	return sum
}

typedef std::vector<double> vector;
typedef std::vector<std::vector<double>> matrix;

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

vector operator * (matrix matr, vector vec)
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

matrix operator *(matrix A, matrix B)
{
	matrix C(A.size(), vector(A.size(), 0));
	for (auto i = 0; i < A.size(); i++)
		for (auto j = 0; j < A.size(); j++)
			for (auto k = 0; k < A.size(); k++)
				C[i][j] += A[i][k] * B[k][j];

	return C;
}

std::tuple<vector, matrix, vector> init(int n, double h, int N, double a, vector x)
{
	int size = n * N, k = 0;
	double c = h / 2;

	double a_, b_;

	vector ksi, free_members;
	matrix matr;

	for (auto i = 0; i < size; i++)
	{
		vector row;

		a_ = a, b_ = h;

		for (auto j = 0; j < size; j++)
		{
			if (i == 0)
				ksi.push_back(get_ksi(a_, b_, x.at(k)));

			if (i == j)
				row.push_back(1 - c * get_w(x.at(k)) * K(ksi.at(i), ksi.at(i)));
			else
				row.push_back(-1. * (c * get_w(x.at(k)) * K(ksi.at(i), ksi.at(j))));

			k++;
			if (k == n)
			{
				k = 0;

				if (i == 0)
				{
					a_ += h;
					b_ += h;
				}
			}
		}

		matr.push_back(row);
		free_members.push_back(f(ksi.at(i)));
	}

	return std::make_tuple(ksi, matr, free_members);
}

vector Gauss(matrix A, vector b)
{
	int n = b.size();
	int k = 0, index;
	double max;

	vector x(n);
	vector y(n, 0);

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

		if (max < 0.0000001)
			throw std::exception("max is 0");

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

			if (abs(tmp) < 0.0000001)
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

std::tuple<matrix, matrix> QR(matrix A)
{
	matrix Q, R = A, Z = A, minor(A.size(), vector(A.size(), 0));

	std::vector<matrix> H;

	for (auto k = 0; k < A.size() - 1; k++)
	{
		for (int i = 0; i < k; i++)
			minor[i][i] = 1.;
		for (int i = k; i < A.size(); i++)
			for (int j = k; j < A.size(); j++)
				minor[i][j] = Z[i][j];

		double tmp_sum = 0;
		vector x, e;
		for (auto i = 0; i < A.size(); i++)
		{
			x.push_back(A[i][k]);
			e.push_back((i == k) ? 1 : 0);

			tmp_sum += x.at(i) * x.at(i);
		}
		double a = sqrt(tmp_sum);
		if (A[k][k] > 0)
			a = -a;

		tmp_sum = 0;
		for (auto i = 0; i < A.size(); i++)
		{
			e.at(i) = x.at(i) + a * e.at(i);
			tmp_sum += e.at(i) * e.at(i);
		}
		double e_norm = sqrt(tmp_sum);

		for (auto i = 0; i < A.size(); i++)
			e.at(i) /= e_norm;

		matrix Hk(A.size(), vector(A.size(), 0));

		for (int i = 0; i < A.size(); i++)
			for (int j = 0; j < A.size(); j++)
				Hk[i][j] = -2 * e.at(i) * e.at(j);
		for (int i = 0; i < A.size(); i++)
			Hk[i][i] += 1;

		H.push_back(Hk);

		Z = H.at(k) * minor;
	}

	Q = H.at(0);
	for (auto i = 1; i < A.size() - 1; i++)
	{
		minor = H.at(i) * Q;
		Q = minor;
	}

	R = Q * A;
	for (auto i = 0; i < Q.size(); i++)
		for (auto j = 0; j < i; j++)
		{
			double t = Q[i][j];
			Q[i][j] = Q[j][i];
			Q[j][i] = t;
		}

	return std::make_tuple(Q, R);
}

vector solvebyQR(matrix A, vector b)
{
	matrix Q, R;
	std::tie(Q, R) = QR(A);
	
	for (auto i = 0; i < Q.size(); i++)
		for (auto j = 0; j < i; j++)
		{
			double t = Q[i][j];
			Q[i][j] = Q[j][i];
			Q[j][i] = t;
		}

	std::vector<double> x(A.size()), y = Q * b;

	double sum = 0;
	for (int i = A.size() - 1; i >= 0; i--)
	{
		for (auto k = i + 1; k < A.size(); k++)
			sum += x.at(k) * (R[i][k] / R[i][i]);
		x.at(i) = y.at(i) / R[i][i] - sum;
		sum = 0;
	}

	return x;
}

int main()
{
	int k = 0;
	const double a = 0, b = M_PI;
	const int n = 3, ratio = pow(1 << n, 2);

	double h = (b - a), error, prev_error;

	vector x = { -sqrt(3. / 5.), 0, sqrt(3. / 5.) };

	std::string goon = "y";

	while (goon == "y")
	{
		int N = (b - a) / h;
		std::cout << "N = " << N << '\n';
		std::cout << "Size = " << n * N << '\n';

		matrix A, Q, R;
		vector ksi, c, u_real, u_appr;

		std::tie(ksi, A, c) = init(n, h, N, a, x);

		/*for (auto i = 0; i < n * N; i++)
		{
			for (auto j = 0; j < n * N; j++)
				std::cout << A[i][j] << "   ";
			std::cout << '\n';
		}*/

		//try {
			//u_appr = Gauss(A, c);
			u_appr = solvebyQR(A, c);
		/*}
		catch (std::exception) {
			std::cout << "Gauss says max is 0" << '\n';
			goon = "n";
			continue;
		}*/

		for (auto i = 0; i < n * N; i++)
			u_real.push_back(ksi.at(i));

		for (auto i = 0; i < n * N; i++)
			std::cout << u(ksi.at(i)) << "  ~  " << u_appr.at(i) <<'\n';

		error = fabs(u(ksi.at(0)) - u_appr.at(0));

		for (auto i = 0; i < n * N; i++)
			fabs(u(ksi.at(i)) - u_appr.at(i)) > error ? error = fabs(u(ksi.at(i)) - u_appr.at(i)) : error;

		std::cout << '\n' << error << '\n' << '\n';

		if (k != 0)
			std::cout << "Expected error ratio: " << ratio << '\n' << std::setprecision(10)
			<< "Actual error ratio: " << prev_error / error << '\n' << '\n';

		matrix().swap(A);
		matrix().swap(Q);
		matrix().swap(R);

		vector().swap(ksi);
		vector().swap(c);
		vector().swap(u_appr);

		std::cout << '\n' << "Continue(y/n)?: ";
		std::cin >> goon;
		std::cout << '\n';

		k++;

		h /= 2;

		prev_error = error;
	}
}