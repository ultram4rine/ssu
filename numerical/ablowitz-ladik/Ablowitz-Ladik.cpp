#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <complex>
#include <tuple>

typedef std::vector<double> vector;
typedef std::vector<std::complex<double>> cvector;
typedef std::vector<cvector> matrix;
typedef std::vector<std::complex<double>> diag;

std::ostream& operator << (std::ostream& os, const cvector& v)
{
	std::stringstream buffer;

	for (auto i = v.begin(); i != v.end(); i++)
		buffer << *i << '\n';

	return os << buffer.str();
}

cvector operator+ (cvector vector, double term)
{
	cvector new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		*i += term;

	return new_vector;
}

cvector operator- (cvector vector, double deductible)
{
	cvector new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		*i -= deductible;

	return new_vector;
}

cvector operator* (double multiplier, cvector vector)
{
	cvector new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		*i *= multiplier;

	return new_vector;
}

cvector operator* (cvector vector, double multiplier)
{
	cvector new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		*i *= multiplier;

	return new_vector;
}

cvector operator/ (cvector vector, double divider)
{
	cvector new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		*i /= divider;

	return new_vector;
}

cvector operator+ (cvector a, cvector b)
{
	cvector new_vector;

	for (auto i = 0; i < a.size(); i++)
		new_vector.push_back(a.at(i) + b.at(i));

	return new_vector;
}

cvector operator- (cvector a, cvector b)
{
	cvector new_vector;

	for (auto i = 0; i < a.size(); i++)
		new_vector.push_back(a.at(i) - b.at(i));

	return new_vector;
}

std::vector<cvector> operator>> (std::vector<cvector> v, cvector element)
{
	v.at(0) = v.at(1);
	v.at(1) = v.at(2);
	v.at(2) = element;

	return v;
}

matrix operator *(std::complex<double> b, matrix A)
{
	matrix C(A.size());
	for (auto i = 0; i < C.size(); i++)
		for (auto j = 0; j < C.size(); j++)
			C[i][j] *= b;
	return C;
}

matrix operator *(diag D, matrix A)
{
	matrix B(A.size());
	for (auto i = 0; i < A.size(); i++)
		for (auto j = 0; j < A.size(); j++)
			B[i][j] = A[i][j] * D[i];
	return B;
}

matrix operator *(matrix A, matrix B)
{
	matrix C(A.size(), cvector(A.size(), 0));
	for (auto i = 0; i < A.size(); i++)
		for (auto j = 0; j < A.size(); j++)
			for (auto k = 0; k < A.size(); k++)
				C[i][j] += A[i][k] * B[k][j];
	return C;
}

double q(double t)
{
	return pow(sin((1 / 2) * t), 3) + 1;
}

cvector F(double t, std::complex<double> zeta, cvector v)
{
	using namespace std::complex_literals;

	cvector res;

	res.push_back(q(t) * v.at(1) - 1i * zeta * v.at(0));
	res.push_back(-1 * q(t) * v.at(0) + 1i * zeta * v.at(1));

	return res;
}

cvector AdamsPredictor(int n, double t, double grid_start, double grid_end, std::vector<cvector> fs, std::vector<cvector> approximation)
{
	double h = (grid_end - grid_start) / n;
	cvector predictor, k;

	k = 23 * fs.at(2) - 16 * fs.at(1) + 5 * fs.at(0);

	//F(t + 2 * h, approximation.at(2))

	predictor = approximation.at(2) + h / 12 * k;

	return predictor;
}

cvector AdamsCorrector(int n, double t, std::complex<double> xi, double grid_start, double grid_end, cvector prediction, std::vector<cvector> fs, std::vector<cvector> approximation)
{
	double h = (grid_end - grid_start) / n;
	cvector correction, fi = prediction;
	int j = 0;

	do
	{
		correction = fi;
		cvector k;

		k = 5 * F(t + 3 * h, xi, correction) + 8 * fs.at(2) - fs.at(1);
		fi = approximation.at(2) + h / 12 * k;

		//k = 9 * F(t + 3 * h, correction) + 19 * fs.at(2) - 5 * fs.at(1) + fs.at(0);
		//fi = approximation.at(2) + h / 24 * k;

		j++;
	} while (std::abs(correction.at(0) - fi.at(0)) > DBL_EPSILON&& std::abs(correction.at(1) - fi.at(1)) > DBL_EPSILON&& std::abs(correction.at(2) - fi.at(2)) > DBL_EPSILON);

	//fabs(correction.at(0) - fi.at(0)) > DBL_EPSILON&&fabs(correction.at(1) - fi.at(1)) > DBL_EPSILON&&fabs(correction.at(2) - fi.at(2)) > DBL_EPSILON

	correction = fi;

	return correction;
}

std::tuple<std::vector<cvector>, std::vector<cvector>> ExplicitRungeKutta(int n, int accuracy_order, double grid_start, double grid_end, cvector f0, bool for_init)
{
	double h = (grid_end - grid_start) / n, t = h;
	std::complex<double> xi;
	std::vector<cvector> approximations, fs;

	approximations.push_back(f0);

	if (for_init)
	{
		n = accuracy_order - 1;
		fs.push_back(F(t - h, xi, approximations.at(0)));
	}

	for (auto i = 0; i < n; i++)
	{
		t -= h;
		cvector f, k1, k2, k3;

		k1 = h * F(t, xi, f0);

		k2 = h * F(t + h / 2, xi, f0 + k1 / 2);

		k3 = h * F(t + h, xi, f0 + 2 * k2 - k1);

		f = f0 + (k1 + 4 * k2 + k3) / 6;

		approximations.push_back(f);
		if (for_init)
			fs.push_back(F(t + h, xi, approximations.at(i + 1.0)));

		f0 = f;
		t += 2 * h;
	}

	return std::make_tuple(fs, approximations);
}

std::vector<cvector> ImplicitAdamsPC(int n, std::complex<double> xi, int accuracy_order, double grid_start, double grid_end, cvector f0)
{
	double t = 0, h = (grid_end - grid_start) / n;
	cvector correction, prediction;
	std::vector<cvector> fs, approximation, approximation_on_grid;

	std::tie(fs, approximation) = ExplicitRungeKutta(n, accuracy_order, grid_start, grid_end, f0, true);

	for (auto i = approximation.begin(); i != approximation.end(); i++)
		approximation_on_grid.push_back(*i);

	for (auto j = accuracy_order; j <= n; j++)
	{
		prediction = AdamsPredictor(n, t, grid_start, grid_end, fs, approximation);
		correction = AdamsCorrector(n, t, xi, grid_start, grid_end, prediction, fs, approximation);

		fs = (fs >> F(t + 3 * h, xi, correction));
		approximation = (approximation >> correction);

		t = t + h;

		approximation_on_grid.push_back(correction);
	}

	return approximation_on_grid;
}

cvector AL(double eps, double T1, double T2, double M, std::complex<double> zeta)
{
	using namespace std::complex_literals;

	std::vector<matrix> Tau;
	for (auto m = 0; m < M; m++)
	{
		cvector row1(2), row2(2);
		row1.at(0) = pow(M_E, 1i * zeta * eps);
		row1.at(1) = eps * q(T1 + m * eps);
		row2.at(0) = -row1.at(1);
		row2.at(1) = pow(row1.at(0), -1);

		matrix tmp = { row1,row2 };

		Tau.push_back((1 / sqrt(1 + pow(eps, 2) * fabs(q(T1 + m * eps)))) * tmp);
	}

	diag D = { pow(M_E, 1i * zeta * (T2 + 0.5 * eps)), pow(M_E, -1i * zeta * (T2 + 0.5 * eps)) };
	matrix mult = D * Tau.at(M);

	for (auto m = M - 1; m >= 0; m--)
		mult = mult * Tau.at(m);

	mult = pow(M_E, -1i * zeta * (T1 - 0.5 * eps)) * mult;
	for (auto i = 0; i < mult.size(); i++) {
		for (auto j = 0; j < mult.size(); j++)
			std::cout << mult[i][j] << "  ";
		std::cout << '\n';
	}

	return cvector(0);
}

int main()
{
	int k = 3;

	int M = 10;
	double T1 = 0, T2 = M_PI;
	double eps = (T2 - T1) / M;

	double xi = 0.5, eta = 0.5;
	std::complex<double> zeta = { xi, eta };

	double min_error, errorImAdams, prev_errorImAdams;

	std::string goon = "n";

	cvector f0 = { 0, 2, 1 };
	std::vector<cvector> approximation_by_RK3, approximation_by_ImAdams;

	std::cout << "Initial values: t = " << T1 << '\n'
		<< "x(t) = " << f0.at(0) << '\n'
		<< "y(t) = " << f0.at(1) << '\n'
		<< "z(t) = " << f0.at(2) << '\n' << '\n';

	cvector fake = AL(eps, T1, T2, M, zeta);

	while (goon == "y")
	{
		double eps = (T2 - T1) / M;

		std::cout << "eps = " << eps << '\n'
			<< "Number of nodes = " << M << '\n' << '\n';

		approximation_by_ImAdams = ImplicitAdamsPC(M, xi, k, T1, T2, f0);

		std::cout << std::setprecision(5);

		for (auto i = approximation_by_ImAdams.begin(); i != approximation_by_ImAdams.end(); i++)
		{
			/*std::cout << "t = " << j << '\n'
				<< "x(t) = " << x(j, C) << "   ~x(t) = " << i->at(0) << "   x(t) - ~x(t) = " << x(j, C) - i->at(0) << '\n'
				<< "y(t) = " << y(j, C) << "   ~y(t) = " << i->at(1) << "   y(t) - ~y(t) = " << y(j, C) - i->at(1) << '\n'
				<< "z(t) = " << z(j, C) << "   ~z(t) = " << i->at(2) << "   z(t) - ~z(t) = " << z(j, C) - i->at(2) << '\n' << '\n';
			*/
		}
	}

	return 0;
}