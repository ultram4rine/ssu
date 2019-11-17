#include <iostream>
#include <cmath>

using namespace std;

//Functions
//*not used in code*

double Sin(double x)
{
	return sin(x);
}

double mod_Sin(double x)
{
	return fabs(sin(x));
}

double Power(double x, double a)
{
	return pow(x, a);
}

double Custom(double x, double a)
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

double Sin_derivative_finite_difference(double x, double h)
{
	return (sin(x + h) - sin(x)) / h;
}

double mod_Sin_derivative_finite_difference(double x, double h)
{
	return (fabs(sin(x + h)) - fabs(sin(x))) / h;
}

double Power_derivative_finite_difference(double x, double a, double h)
{
	return (pow(x + h, a) - pow(x, a)) / h;
}

double Custom_derivative_finite_difference(double x, double a, double h)
{
	return (pow(x + h, a) * sin(1 / (x + h)) - pow(x, a) * sin(1 / x)) / h;
}

int main()
{
	double h, x, a;

	cout << "Write h: ";
	cin >> h;

	cout << "Write x: ";
	cin >> x;

	cout << "Write a: ";
	cin >> a;

	cout << "Diff\n";

	cout << fabs(Sin_derivative(x) - Sin_derivative_finite_difference(x, h)) << '\n';

	cout << fabs(mod_Sin_derivative(x) - mod_Sin_derivative_finite_difference(x, h)) << '\n';

	cout << fabs(Power_derivative(x, a) - Power_derivative_finite_difference(x, a, h)) << '\n';

	cout << fabs(Custom_derivative(x, a) - Custom_derivative_finite_difference(x, a, h)) << '\n';
}
