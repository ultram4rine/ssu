#include "pch.h"

#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>

std::vector<double> F(double t, std::vector<double> u)
{
	std::vector<double> res;

	res.push_back(2 * u.at(0) - u.at(1) + u.at(2));
	res.push_back(u.at(0) + 2 * u.at(1) - u.at(2));
	res.push_back(u.at(0) - u.at(1) + 2 * u.at(2));

	return res;
}

//Answers
double x(double t, std::vector<double> C) { return C.at(1) * pow(M_E, 2 * t) + C.at(2) * pow(M_E, 3 * t); }

double y(double t, std::vector<double> C) { return C.at(0) * pow(M_E, t) + C.at(1) * pow(M_E, 2 * t); }

double z(double t, std::vector<double> C) { return C.at(0) * pow(M_E, t) + C.at(1) * pow(M_E, 2 * t) + C.at(2) * pow(M_E, 3 * t); }
//End of answers block

double r(double value, int k)
{
	return (double)round((pow(10, k) * value)) / pow(10, k);
}

std::ostream& operator << (std::ostream& os, const std::vector<double>& v)
{
	std::stringstream buffer;

	for (auto i = v.begin(); i != v.end(); i++)
		buffer << *i << '\n';

	return os << buffer.str();
}

std::vector<double> operator+ (std::vector<double> vector, double term)
{
	std::vector<double> new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		* i += term;

	return new_vector;
}

std::vector<double> operator- (std::vector<double> vector, double deductible)
{
	std::vector<double> new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		* i -= deductible;

	return new_vector;
}

std::vector<double> operator* (double multiplier, std::vector<double> vector)
{
	std::vector<double> new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		* i *= multiplier;

	return new_vector;
}

std::vector<double> operator* (std::vector<double> vector, double multiplier)
{
	std::vector<double> new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		* i *= multiplier;

	return new_vector;
}

std::vector<double> operator/ (std::vector<double> vector, double divider)
{
	std::vector<double> new_vector = vector;

	for (auto i = new_vector.begin(); i != new_vector.end(); i++)
		* i /= divider;

	return new_vector;
}

std::vector<double> operator+ (std::vector<double> a, std::vector<double> b)
{
	std::vector<double> new_vector;

	for (auto i = 0; i < a.size(); i++)
		new_vector.push_back(a.at(i) + b.at(i));

	return new_vector;
}

std::vector<double> operator- (std::vector<double> a, std::vector<double> b)
{
	std::vector<double> new_vector;

	for (auto i = 0; i < a.size(); i++)
		new_vector.push_back(a.at(i) - b.at(i));

	return new_vector;
}

std::vector<std::vector<double>> operator>> (std::vector<std::vector<double>> v, std::vector<double> element)
{
	v.at(0) = v.at(1);
	v.at(1) = v.at(2);
	v.at(2) = element;

	return v;
}

std::vector<double> AdamsPredictor(int n, double t, double grid_start, double grid_end, std::vector<std::vector<double>> fs, std::vector<std::vector<double>> approximation)
{
	double h = (grid_end - grid_start) / n;
	std::vector<double> predictor, k;

	k = 23 * fs.at(2) - 16 * fs.at(1) + 5 * fs.at(0);

	//F(t + 2 * h, approximation.at(2))

	predictor = approximation.at(2) + h / 12 * k;

	return predictor;
}

std::vector<double> AdamsCorrector(int n, double t, double grid_start, double grid_end, std::vector<double> prediction, std::vector<std::vector<double>> fs, std::vector<std::vector<double>> approximation)
{
	double h = (grid_end - grid_start) / n;
	std::vector<double> correction, fi = prediction;
	int j = 0;

	do
	{
		correction = fi;
		std::vector<double> k;

		k = 5 * F(t + 3 * h, correction) + 8 * fs.at(2) - fs.at(1);
		fi = approximation.at(2) + h / 12 * k;

		//k = 9 * F(t + 3 * h, correction) + 19 * fs.at(2) - 5 * fs.at(1) + fs.at(0);
		//fi = approximation.at(2) + h / 24 * k;

		j++;
	} while (j<=3);

	//fabs(correction.at(0) - fi.at(0)) > DBL_EPSILON&&fabs(correction.at(1) - fi.at(1)) > DBL_EPSILON&&fabs(correction.at(2) - fi.at(2)) > DBL_EPSILON

	correction = fi;

	return correction;
}

std::tuple<std::vector<std::vector<double>>, std::vector<std::vector<double>>> ExplicitRungeKutta(int n, int accuracy_order, double grid_start, double grid_end, std::vector<double> f0, bool for_init)
{
	double h = (grid_end - grid_start) / n, t = h;
	std::vector<std::vector<double>> approximations, fs;

	approximations.push_back(f0);

	if (for_init)
	{
		n = accuracy_order - 1;
		fs.push_back(F(t - h, approximations.at(0)));
	}

	for (auto i = 0; i < n; i++)
	{
		t -= h;
		std::vector<double> f, k1, k2, k3;

		k1 = h * F(t, f0);

		k2 = h * F(t + h / 2, f0 + k1 / 2);

		k3 = h * F(t + h, f0 + 2 * k2 - k1);

		f = f0 + (k1 + 4 * k2 + k3) / 6;

		approximations.push_back(f);
		if (for_init)
			fs.push_back(F(t + h, approximations.at(i + 1.0)));

		f0 = f;
		t += 2 * h;
	}

	return std::make_tuple(fs, approximations);
}

std::vector<std::vector<double>> ExplicitAdams(int n, int accuracy_order, double grid_start, double grid_end, std::vector<double> f0)
{
	double t = 0, h = (grid_end - grid_start) / n;
	std::vector<std::vector<double>> fs, approximation, approximation_on_grid;

	std::tie(fs, approximation) = ExplicitRungeKutta(n, accuracy_order, grid_start, grid_end, f0, true);

	for (auto i = approximation.begin(); i != approximation.end(); i++)
		approximation_on_grid.push_back(*i);

	for (auto j = accuracy_order; j <= n; j++)
	{
		std::vector<double> f, k;

		std::vector<double> f_new = F(t + 2 * h, approximation.at(2));

		k = 23 * f_new - 16 * fs.at(1) + 5 * fs.at(0);
		f = approximation.at(2) + h / 12 * k;

		fs.at(0) = fs.at(1);
		fs.at(1) = f_new;

		approximation = (approximation >> f);

		t = t + h;

		approximation_on_grid.push_back(f);
	}

	return approximation_on_grid;
}

std::vector<std::vector<double>> ImplicitAdamsPC(int n, int accuracy_order, double grid_start, double grid_end, std::vector<double> f0)
{
	double t = 0, h = (grid_end - grid_start) / n;
	std::vector<double> correction, prediction;
	std::vector<std::vector<double>> fs, approximation, approximation_on_grid;

	std::tie(fs, approximation) = ExplicitRungeKutta(n, accuracy_order, grid_start, grid_end, f0, true);

	for (auto i = approximation.begin(); i != approximation.end(); i++)
		approximation_on_grid.push_back(*i);

	for (auto j = accuracy_order; j <= n; j++)
	{
		prediction = AdamsPredictor(n, t, grid_start, grid_end, fs, approximation);
		correction = AdamsCorrector(n, t, grid_start, grid_end, prediction, fs, approximation);

		fs = (fs >> F(t + 3 * h, correction));
		approximation = (approximation >> correction);

		t = t + h;

		approximation_on_grid.push_back(correction);
	}

	return approximation_on_grid;
}

int main()
{
	const int k = 3; int i = 0, n = 10;
	double grid_start = 0, grid_end = 1, j = grid_start;
	double min_error, errorRK3, errorExAdams, errorImAdams, prev_errorRK3, prev_errorExAdams, prev_errorImAdams;

	std::string goon = "y";

	std::vector<double> f0 = { 0, 2, 1 }, C = { 1, 1, -1 };
	std::vector<std::vector<double>> by_effect, approximation_by_RK3, approximation_by_ExAdams, approximation_by_ImAdams;

	std::cout << "Initial values: t = " << grid_start << '\n'
		<< "x(t) = " << f0.at(0) << '\n'
		<< "y(t) = " << f0.at(1) << '\n'
		<< "z(t) = " << f0.at(2) << '\n' << '\n';

	while (goon == "y")
	{
		double h = (grid_end - grid_start) / n;

		std::cout << "h = " << h << '\n'
			<< "Number of nodes = " << n << '\n' << '\n';

		std::tie(by_effect, approximation_by_RK3) = ExplicitRungeKutta(n, k, grid_start, grid_end, f0, false);
		approximation_by_ExAdams = ExplicitAdams(n, k, grid_start, grid_end, f0);
		approximation_by_ImAdams = ImplicitAdamsPC(n, k, grid_start, grid_end, f0);

		std::cout << std::setprecision(5);

		for (auto i = approximation_by_RK3.begin(); i != approximation_by_RK3.end(); i++)
		{
			/*std::cout << "t = " << j << '\n'
				<< "x(t) = " << x(j, C) << "   ~x(t) = " << i->at(0) << "   x(t) - ~x(t) = " << x(j, C) - i->at(0) << '\n'
				<< "y(t) = " << y(j, C) << "   ~y(t) = " << i->at(1) << "   y(t) - ~y(t) = " << y(j, C) - i->at(1) << '\n'
				<< "z(t) = " << z(j, C) << "   ~z(t) = " << i->at(2) << "   z(t) - ~z(t) = " << z(j, C) - i->at(2) << '\n' << '\n';
			*/

			fabs(x(j, C) - i->at(0)) > fabs(y(j, C) - i->at(1)) ? errorRK3 = fabs(x(j, C) - i->at(0)) : errorRK3 = fabs(y(j, C) - i->at(1));
			fabs(z(j, C) - i->at(2)) > errorRK3 ? errorRK3 = fabs(z(j, C) - i->at(2)) : errorRK3 = errorRK3;

			j += h;
		}
		j = 0;
		for (auto i = approximation_by_ExAdams.begin(); i != approximation_by_ExAdams.end(); i++)
		{
			/*std::cout << "t = " << j << '\n'
				<< "x(t) = " << x(j, C) << "   ~x(t) = " << i->at(0) << "   x(t) - ~x(t) = " << x(j, C) - i->at(0) << '\n'
				<< "y(t) = " << y(j, C) << "   ~y(t) = " << i->at(1) << "   y(t) - ~y(t) = " << y(j, C) - i->at(1) << '\n'
				<< "z(t) = " << z(j, C) << "   ~z(t) = " << i->at(2) << "   z(t) - ~z(t) = " << z(j, C) - i->at(2) << '\n' << '\n';
			*/

			fabs(x(j, C) - i->at(0)) > fabs(y(j, C) - i->at(1)) ? errorExAdams = fabs(x(j, C) - i->at(0)) : errorExAdams = fabs(y(j, C) - i->at(1));
			fabs(z(j, C) - i->at(2)) > errorExAdams ? errorExAdams = fabs(z(j, C) - i->at(2)) : errorExAdams = errorExAdams;

			j += h;
		}
		j = 0;
		for (auto i = approximation_by_ImAdams.begin(); i != approximation_by_ImAdams.end(); i++)
		{
			/*std::cout << "t = " << j << '\n'
				<< "x(t) = " << x(j, C) << "   ~x(t) = " << i->at(0) << "   x(t) - ~x(t) = " << x(j, C) - i->at(0) << '\n'
				<< "y(t) = " << y(j, C) << "   ~y(t) = " << i->at(1) << "   y(t) - ~y(t) = " << y(j, C) - i->at(1) << '\n'
				<< "z(t) = " << z(j, C) << "   ~z(t) = " << i->at(2) << "   z(t) - ~z(t) = " << z(j, C) - i->at(2) << '\n' << '\n';
			*/

			fabs(x(j, C) - i->at(0)) > fabs(y(j, C) - i->at(1)) ? errorImAdams = fabs(x(j, C) - i->at(0)) : errorImAdams = fabs(y(j, C) - i->at(1));
			fabs(z(j, C) - i->at(2)) > errorImAdams ? errorImAdams = fabs(z(j, C) - i->at(2)) : errorImAdams = errorImAdams;

			j += h;
		}
		j = 0;

		std::cout << std::setprecision(10)
			<< "Error by RK3: " << errorRK3 << '\n'
			<< "Error by ExA: " << errorExAdams << '\n'
			<< "Error by ImA: " << errorImAdams << '\n' << '\n';

		if (i != 0)
			std::cout << "Expected error ratio: " << (1 << k) << '\n' << std::setprecision(10)
			<< "Error ratio for RK3: " << prev_errorRK3 / errorRK3 << '\n'
			<< "Error ratio for ExA: " << prev_errorExAdams / errorExAdams << '\n'
			<< "Error ratio for ImA: " << prev_errorImAdams / errorImAdams << '\n' << '\n';

		errorRK3 > errorExAdams ? min_error = errorExAdams : min_error = errorRK3;
		min_error > errorImAdams ? min_error = errorImAdams : min_error = min_error;

		std::cout << "Minimal error: " << min_error << '\n' << '\n';

		std::cout << '\n' << "Continue(y/n)?: ";
		std::cin >> goon;

		i++;

		n *= 2;

		prev_errorRK3 = errorRK3;
		prev_errorExAdams = errorExAdams;
		prev_errorImAdams = errorImAdams;
	}

	return 0;
}