#include "pch.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//Function
double func(float x, float e)
{
	float c, s = 0;
	int k = 0;
	c = 1;
	while (fabs(c) >= e)
	{
		s += c;
		c *= -x / ((2 * k + 1)*(2 * k + 2));
		k++;
	}
	return s;
}

//Derivative of Function
double derivative(float x, float e)
{
	float c, s = 0;
	int k = 1;
	c = -0.5;
	while (fabs(c) >= e)
	{
		s += c;
		c *= -x / ((2 * k) * (2 * k + 1));
		k++;
	}
	return s;
}

int main() {
	double a, b, h, e, f, d, x;
	double *valfunc = new double[18]; //Values of Function
	double *valder = new double[18]; //Values of Derivative
	int i;
	a = 0;
	b = 1.7;
	h = 0.1;
	e = 0.0001;
	cout << "x" << "\t" << "f(x)" << "\n" << "\n";
	for (x = a, i = 0; x <= b + 0.1; x += h, i++)
	{
		f = func(x, e);
		valfunc[i] = f;
		cout << x << "\t" << f << "\n";
	}
	cout << "\n";
	cout << "x" << "\t" << "f'(x)" << "\n" << "\n";
	for (x = a, i = 0; x <= b + 0.1; x += h, i++)
	{
		d = derivative(x, e);
		valder[i] = d;
		cout << x << "\t" << d << "\n";
	}
	cout << "\n";
	double *fplus = new double[18];
	double *fminus = new double[18];
	double *fzero = new double[18];
	for (i = 0; i <= 16; i++)
	{
		fplus[i] = (valfunc[i + 1] - valfunc[i]) / h;
		cout << "fplus[" << i + 1 << "]=" << fplus[i] << '\n';
	}
	cout << "\n";
	for (i = 1; i <= 17; i++)
	{
		fminus[i] = (valfunc[i] - valfunc[i - 1]) / h;
		cout << "fminus[" << i << "]=" << fminus[i] << '\n';
	}
	cout << "\n";
	for (i = 1; i <= 16; i++)
	{
		fzero[i] = (valfunc[i + 1] - valfunc[i - 1]) / (2 * h);
		cout << "fzero[" << i << "]=" << fzero[i] << '\n';
	}
	cout << '\n';
	double *valplus = new double[18];
	double *valminus = new double[18];
	double *valzero = new double[18];
	for (i = 0; i < 17; i++)
	{
		valplus[i] = abs(valder[i] - fplus[i]);
		valminus[i] = abs(valder[i] - fminus[i]);
		valzero[i] = abs(valder[i] - fzero[i]);
	}
	double zplus, zminus, zzero;
	zplus = valplus[0];
	zminus = valminus[0];
	zzero = valzero[0];
	for (i = 0; i < 17; i++)
	{
		if (valplus[i + 1] > valplus[i]) zplus = valplus[i];
		if (valminus[i + 1] > valminus[i]) zminus = valminus[i];
		if (valzero[i + 1] > valzero[i]) zzero = valzero[i];
	}
	cout << "zplus = " << zplus << '\n' << '\n' 
		<< "zminus = " << zminus << '\n' << '\n' 
		<< "zzero = " << zzero;
	return 0;
}