#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <tuple>

class Vector;

class Matrix
{
private:
	double* data;
public:
	int m, n;

	Matrix() : m(0), n(0), data(nullptr) {}

	Matrix(int m_, int n_) : Matrix()
	{
		m = m_;
		n = n_;
		allocate(m_, n_);
	}

	Matrix(const Matrix& mat) : Matrix(mat.m, mat.n)
	{

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				(*this)(i, j) = mat(i, j);
	}

	template<int rows, int cols>
	Matrix(double(&a)[rows][cols]) : Matrix(rows, cols)
	{

		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				(*this)(i, j) = a[i][j];
	}

	~Matrix()
	{
		deallocate();
	}

	double& operator() (int i, int j)
	{
		return data[i + m * j];
	}

	double  operator() (int i, int j) const
	{
		return data[i + m * j];
	}

	Matrix& operator=(const Matrix& source)
	{
		if (this != &source) 
		{
			if ((m * n) != (source.m * source.n))
				allocate(source.m, source.n);
			std::copy(source.data, source.data + source.m * source.n, data);
		}
		return *this;
	}

	void compute_minor(const Matrix& mat, int d)
	{
		allocate(mat.m, mat.n);

		for (int i = 0; i < d; i++)
			(*this)(i, i) = 1.0;
		for (int i = d; i < mat.m; i++)
			for (int j = d; j < mat.n; j++)
				(*this)(i, j) = mat(i, j);
	}

	void mult(const Matrix& a, const Matrix& b)
	{
		if (a.n != b.m) {
			std::cerr << "Matrix multiplication not possible, sizes don't match !\n";
			return;
		}

		if (a.m != m or b.n != n)
			allocate(a.m, b.n);

		memset(data, 0, m * n * sizeof(double));

		for (int i = 0; i < a.m; i++)
			for (int j = 0; j < b.n; j++)
				for (int k = 0; k < a.n; k++)
					(*this)(i, j) += a(i, k) * b(k, j);

	}

	void transpose() {
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < i; j++) {
				double t = (*this)(i, j);
				(*this)(i, j) = (*this)(j, i);
				(*this)(j, i) = t;
			}
		}
	}

	void extract_column(Vector& v, int c);

	void allocate(int m_, int n_)
	{
		deallocate();

		m = m_;
		n = n_;

		data = new double[m_ * n_];
		memset(data, 0, m_ * n_ * sizeof(double));

	}

	void deallocate()
	{
		if (data)
			delete[] data;

		data = nullptr;
	}
};

class Vector
{
private:
	double* data;
public:
	int size;

	Vector() : size(0), data(nullptr) {}

	Vector(int size_) : Vector()
	{
		size = size_;
		allocate(size_);
	}

	~Vector()
	{
		deallocate();
	}

	double& operator() (int i)
	{
		return data[i];
	}

	double  operator() (int i) const
	{
		return data[i];
	}

	Vector& operator=(const Vector& source)
	{
		if (this != &source) {
			if (size != (source.size))
				allocate(source.size);
			std::copy(source.data, source.data + source.size, data);
		}
		return *this;
	}

	void allocate(int size_)
	{
		deallocate();

		size = size_;

		data = new double[size_];
		memset(data, 0, size_ * sizeof(double));
	}

	void deallocate()
	{
		if (data)
			delete[] data;

		data = nullptr;

	}

	double norm()
	{
		double sum = 0;
		for (int i = 0; i < size; i++) sum += (*this)(i) * (*this)(i);
		return sqrt(sum);
	}

	void rescale(double factor) {
		for (int i = 0; i < size; i++) (*this)(i) /= factor;
	}

	void rescale_unit() {
		double factor = norm();
		rescale(factor);
	}
};

void vmadd(const Vector& a, const Vector& b, double s, Vector& c)
{
	if (c.size != a.size or c.size != b.size) {
		std::cerr << "[vmadd]: vector sizes don't match\n";
		return;
	}

	for (int i = 0; i < c.size; i++)
		c(i) = a(i) + s * b(i);
}

void compute_householder_factor(Matrix& mat, const Vector& v)
{

	int n = v.size;
	mat.allocate(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mat(i, j) = -2 * v(i) * v(j);
	for (int i = 0; i < n; i++)
		mat(i, i) += 1;
}

void Matrix::extract_column(Vector& v, int c)
{
	if (m != v.size) {
		std::cerr << "[Matrix::extract_column]: Matrix and Vector sizes don't match\n";
		return;
	}

	for (int i = 0; i < m; i++)
		v(i) = (*this)(i, c);
}

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

std::vector<double> operator * (Matrix matr, std::vector<double> vec)
{
	std::vector<double> res(vec.size());

	for (auto i = 0; i < vec.size(); i++)
	{
		res.at(i) = 0;

		for (auto j = 0; j < vec.size(); j++)
			res.at(i) += matr(i, j) * vec.at(j);
	}

	return res;
}

std::tuple<std::vector<double>, Matrix, std::vector<double>> init(int n, double h, int N, double a, std::vector<double> x)
{
	int size = n * N, k = 0;
	double c = h / 2;

	double a_, b_;

	std::vector<double> ksi, free_members;

	Matrix matrix(size, size);
	for (auto i = 0; i < size; i++)
	{
		a_ = a, b_ = h;

		for (auto j = 0; j < size; j++)
		{
			if (i == 0)
				ksi.push_back(get_ksi(a_, b_, x.at(k)));

			if (i == j)
				matrix(i, i) = (1 - c * get_w(x.at(k)) * K(ksi.at(i), ksi.at(i)));
			else
				matrix(i, j) = -1. * (c * get_w(x.at(k)) * K(ksi.at(i), ksi.at(j)));

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

		free_members.push_back(f(ksi.at(i)));
	}

	return std::make_tuple(ksi, matrix, free_members);
}

std::vector<double> Gauss(Matrix A, std::vector<double> b)
{
	int n = b.size();
	int k = 0, index;
	double max;

	std::vector<double> x(n);
	std::vector<double> y(n, 0);

	while (k < n)
	{
		max = abs(A(k, k));
		index = k;

		for (auto i = k + 1; i < n; i++)
			if (abs(A(i, k)) > max)
			{
				max = abs(A(i, k));
				index = i;
			}

		if (max < 0.000000000001)
			throw std::exception("max is 0");

		for (auto i = 0; i < n; i++)
		{
			double tmp = A(k, i);
			A(k, i) = A(index, i);
			A(index, i) = tmp;
		}

		double tmp = b.at(k);
		b.at(k) = b.at(index);
		b.at(index) = tmp;

		for (auto i = k; i < n; i++)
		{
			double tmp = A(i, k);

			if (abs(tmp) < 0.0000000000000000001)
				continue;

			for (auto j = 0; j < n; j++)
				A(i, j) = A(i, j) / tmp;

			b.at(i) = b.at(i) / tmp;

			if (i == k)
				continue;

			for (auto j = 0; j < n; j++)
				A(i, j) = A(i, j) - A(k, j);

			b.at(i) = b.at(i) - b.at(k);
		}

		k++;
	}

	for (k = n - 1; k >= 0; k--)
	{
		x.at(k) = b.at(k);

		for (auto i = 0; i < k; i++)
			b.at(i) = b.at(i) - A(i, k) * x.at(k);
	}

	return x;
}

std::tuple<Matrix, Matrix> QR(Matrix A)
{
	Matrix Q, R;

	int m = A.m;
	int n = A.n;

	std::vector<Matrix> qv(m);

	Matrix z(A);
	Matrix z1;

	for (int k = 0; k < n && k < m - 1; k++) {

		Vector e(m), x(m);
		double a;

		z1.compute_minor(z, k);

		z1.extract_column(x, k);

		a = x.norm();
		if (A(k, k) > 0) a = -a;

		for (int i = 0; i < e.size; i++)
			e(i) = (i == k) ? 1 : 0;

		vmadd(x, e, a, e);

		e.rescale_unit();

		compute_householder_factor(qv[k], e);

		z.mult(qv[k], z1);
	}

	Q = qv[0];

	for (int i = 1; i < n && i < m - 1; i++) {

		z1.mult(qv[i], Q);
		Q = z1;

	}

	R.mult(Q, A);
	Q.transpose();

	return std::make_tuple(Q, R);
}

std::vector<double> solvebyQR(Matrix A, std::vector<double> b)
{
	Matrix Q, R;

	std::tie(Q, R) = QR(A);
	
	Q.transpose();

	std::vector<double> x(A.n), y = Q * b;

	x = Gauss(R, y);

	/*double sum = 0;
	for (auto i = A.n - 1; i >= 0; i--)
	{
		for (auto k = i + 1; k < A.n; k++)
			sum += x.at(k) * (R(i, k) / R(i, i));
		x.at(i) = y.at(i) / R(i, i) - sum;
	}*/

	return x;
}

int main()
{
	int k = 0;
	const double a = 0, b = M_PI;
	const int n = 3, ratio = pow(1 << n, 2);

	double h = (b - a), error, prev_error;

	std::vector<double> x = { -sqrt(3. / 5.), 0, sqrt(3. / 5.) };

	std::string goon = "y";

	while (goon == "y")
	{
		int N = (b - a) / h;
		std::cout << "N = " << N << '\n';
		std::cout << "Size = " << n * N << '\n';

		Matrix A, Afake, Q, R;
		std::vector<double> ksi, c, u_real, u_appr;

		std::tie(ksi, A, c) = init(n, h, N, a, x);
		std::tie(ksi, Afake, c) = init(n, h, N, a, x);

		/*for (auto i = 0; i < n * N; i++)
		{
			for (auto j = 0; j < n * N; j++)
				std::cout << A[i][j] << "   ";
			std::cout << '\n';
		}*/

		try {
			//u_appr = Gauss(A, c);
			u_appr = solvebyQR(A, c);
		}
		catch (std::exception) {
			std::cout << "Gauss says max is 0" << '\n';
			goon = "n";
			continue;
		}

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

		std::vector<double>().swap(ksi);
		std::vector<double>().swap(c);
		std::vector<double>().swap(u_appr);

		std::cout << '\n' << "Continue(y/n)?: ";
		std::cin >> goon;
		std::cout << '\n';

		k++;

		h /= 2;

		prev_error = error;
	}
}