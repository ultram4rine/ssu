#include <iostream>
#include <cmath>

using namespace std;

typedef double(*function)(double arg);

//Global parameter for power and custom functions
double a;

//Functions

double Sin(double x)
{
	return sin(x);
}

double mod_Sin(double x)
{
	return fabs(sin(x));
}

double Power(double x)
{
	return pow(x, a);
}

double Custom(double x)
{
	return pow(x, a) * sin(1 / x);
}

//Derivatives

//(sin(x))' = cos(x)
//|sin(x)|' = (sin(x) * cos(x)) / |sin(x)|
//(x^a)' = a * x^(a - 1)
//(x^(a) * sin(1 / x))' = a * x^(a - 1) * sin(1 / x) - x^(a - 2) * cos(1 / x)

double Sin_derivative(double x)
{
	return cos(x);
}

double mod_Sin_derivative(double x)
{
	return (sin(x) * cos(x)) / fabs(sin(x));
}

double Power_derivative(double x, double a)
{
	return a * pow(x, a - 1);
}

double Custom_derivative(double x, double a)
{
	return a * pow(x, a - 1) * sin(1 / x) - pow(x, a - 2) * cos(1 / x);
}

//Finite differences

double right_finite_difference(function f, double x, double h)
{
	return (f(x + h) - f(x)) / h;
}

double left_finite_difference(function f, double x, double h)
{
	return (f(x) - f(x - h)) / h;
}

double central_finite_difference(function f, double x, double h)
{
	return (f(x + h) - f(x - h)) / (2 * h);
}

int main()
{
	double h, x;

	cout << "Write h: ";
	cin >> h;

	cout << "Write x: ";
	cin >> x;

	cout << "Write a: ";
	cin >> a;

	//Right
	cout << "Diff for right finite difference\n";

	cout << fabs(Sin_derivative(x) - right_finite_difference(Sin, x, h)) << '\n';

	cout << fabs(mod_Sin_derivative(x) - right_finite_difference(mod_Sin, x, h)) << '\n';

	cout << fabs(Power_derivative(x, a) - right_finite_difference(Power, x, h)) << '\n';

	cout << fabs(Custom_derivative(x, a) - right_finite_difference(Custom, x, h)) << '\n' << '\n';

	//Left
	cout << "Diff for left finite difference\n";

	cout << fabs(Sin_derivative(x) - left_finite_difference(Sin, x, h)) << '\n';

	cout << fabs(mod_Sin_derivative(x) - left_finite_difference(mod_Sin, x, h)) << '\n';

	cout << fabs(Power_derivative(x, a) - left_finite_difference(Power, x, h)) << '\n';

	cout << fabs(Custom_derivative(x, a) - left_finite_difference(Custom, x, h)) << '\n' << '\n';

	//Central
	cout << "Diff for central finite difference\n";

	cout << fabs(Sin_derivative(x) - central_finite_difference(Sin, x, h)) << '\n';

	cout << fabs(mod_Sin_derivative(x) - central_finite_difference(mod_Sin, x, h)) << '\n';

	cout << fabs(Power_derivative(x, a) - central_finite_difference(Power, x, h)) << '\n';

	cout << fabs(Custom_derivative(x, a) - central_finite_difference(Custom, x, h)) << '\n' << '\n';
}
