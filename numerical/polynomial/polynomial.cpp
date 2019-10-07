#include "pch.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

/*
	Formulas for nodes
	Equidistant nodes:   Xk = a + k * h
	Chebyshev nodes:     Xk = (a + b)/2 + ((b - a)/2) * cos(((2 * k + 1) * pi)/(2 * (n + 1)))
*/

//Function to count Equidistant Nodes
double equidistantNodes(double *X, double a, double h, int n)
{
	for (int k = 0; k <= n; k++)
	{
		X[k] = a + k * h;
	}
	return *X;
}

//Function to count Chebyshev Nodes
double ChebyshevNodes(double *X, double a, double b, double pi, int n)
{
	for (int k = 0; k <= n; k++)
	{
		X[k] = (a + b) / 2 + ((b - a) / 2) * cos(((2 * k + 1) * pi) / (2 * (n + 1)));
	}
	return *X;
}

//Function
double function(double x)
{
	double y = x * cos(x);
	return y;
}

//Lagrange's Polynomial
void polynomialLagrange(double *X, double *y, int n)
{
	double *l = new double[n], *L = new double[n];
	for (int k = 0; k <= n; k++)
	{
		l[k] = 1;
		L[k] = 0;
	}
	for (int k = 0; k <= n; k++)
	{
		for (int i = 0; i <= k; i++)
		{
			for (int j = 0; j < i; j++)
			{
				l[i] *= (X[k] - X[j]) / (X[i] - X[j]);
			}
			for (int j = i + 1; j <= n; j++)
			{
				l[i] *= (X[k] - X[j]) / (X[i] - X[j]);
			}
			L[k] += l[i];
		}
	}
	cout << setw(40) << left << "Lagrange's Coefficients"
		<< setw(40) << left << "Interpolation Lagrange Polynomial" << '\n' << '\n';
	for (int k = 0; k <= n; k++)
	{
		cout << setw(40) << left << L[k]
			<< setw(40) << left << L[k] * y[k] << '\n';
	}
}

//Monomials for Newton's Polynomial
double Monomials(double x, double *X, int i)
{
	double monomial = 1;
	for (int j = 0; j < i; j++)
	{
		monomial *= (x - X[j]);
	}
	return monomial;
}

//Newton's Polynomial
void polynomialNewton(double *X, double *y, int n)
{
	double *f = new double[n], *P = new double[n];
	for (int k = 0; k <= n; k++)
	{
		f[k] = y[k];
		P[k] = y[0];
	}
	for (int k = 1; k <= n; k++)
	{
		for (int j = n; j >= k; j--)
		{
			f[j] = (f[j] - f[j - 1]) / (X[j] - X[j - k]);
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			P[i] += Monomials(X[i], X, j) * f[j];
		}
	}
	cout << setw(40) << left << "Divided Differences"
		<< setw(40) << left << "Interpolation Newton Polynomial" << '\n' << '\n';
	for (int k = 0; k <= n; k++)
	{
		cout << setw(40) << left << f[k]
			<< setw(40) << left << P[k] << '\n';
	}
}

//Cubic Spline
void cubSpline(double *X, double *y, double h, int n)
{
	double *A = new double[n], *B = new double[n], *C = new double[n], *D = new double[n];
	double *v = new double[n], *q = new double[n], *S = new double[n];
	for (int k = 0; k <= n; k++)
	{
		A[k] = y[k];
		S[k] = 0;
	}
	q[-1] = 0;
	q[0] = 1;
	for (int j = 1; j <= n - 1; j++)
	{
		v[j] = (6 * (y[j + 1] - 2 * y[j] + y[j - 1])) / h * h;
		q[j] = 4 * q[j - 1] - q[j - 2];
	}
	C[0] = 0;
	C[1] = 0;
	C[n] = 0;
	for (int j = 1; j <= n - 1; j++)
	{
		C[1] += pow(-1, j + 1)*v[j] * q[n - j - 1];
	}
	C[1] /= q[n - 1];
	for (int j = 1; j <= n - 1; j++)
	{
		C[j + 1] = 4 * C[j] - C[j - 1] + v[j];
	}
	for (int j = 1; j <= n; j++)
	{
		D[j] = (C[j] - C[j - 1]) / h;
		B[j] = C[j] * h / 2 - D[j] * (h * h) / 6 + (y[j] - y[j - 1]) / h;
	}
	cout << setw(20) << left << "A"
		<< setw(20) << left << "B"
		<< setw(20) << left << "C"
		<< setw(20) << left << "D"
		<< setw(20) << left << "Spline values" << '\n' << '\n';
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			S[j] = A[j] + B[j] * (X[i] - X[j]) + C[j] * (X[i] - X[j])*(X[i] - X[j]) / 2 + D[j] * (X[i] - X[j])*(X[i] - X[j])*(X[i] - X[j]) / 6;
		}
		cout << setw(20) << left << A[i]
			<< setw(20) << left << B[i]
			<< setw(20) << left << C[i]
			<< setw(20) << left << D[i]
			<< setw(20) << left << S[i] << '\n';
	}
}

//Function of Piecewise Linear Interpolation
void piecewiseLinInterpolFunc(double *X, double *y, int n)
{
	double *A1 = new double[n], *A0 = new double[n], *L = new double[n];
	for (int k = 1; k <= n; k++)
	{
		A1[k - 1] = (y[k] - y[k - 1]) / (X[k] - X[k - 1]);
		A0[k - 1] = y[k - 1] - X[k - 1] * A1[k - 1];
	}
	A1[n] = (y[n] - y[n - 1]) / (X[n] - X[n - 1]);
	A0[n] = y[n - 1] - X[n - 1] * A1[n];
	for (int k = 0; k <= n; k++)
	{
		L[k] = A1[k] * X[k] + A0[k];
		cout << L[k] << '\n';
	}
}

int main()
{
	int n = 10;
	double *equiX = new double[n], *ChebX = new double[n], *FuncInEquiNodes = new double[n], *FuncInChebNodes = new double[n];
	double pi = atan(1) * 4, a = 0, b = 2 * pi, h = (b - a) / n;

	*equiX = equidistantNodes(equiX, a, h, n);
	*ChebX = ChebyshevNodes(ChebX, a, b, pi, n);
	for (int k = 0; k <= n; k++)
	{
		FuncInEquiNodes[k] = function(equiX[k]);
		FuncInChebNodes[k] = function(ChebX[k]);
	}

	cout << setw(40) << left << "Equidistant nodes"
		<< setw(40) << left << "Function in Equidistant nodes" << '\n' << '\n';
	for (int k = 0; k <= n; k++)
	{
		cout << setw(40) << left << equiX[k]
			<< setw(40) << left << FuncInEquiNodes[k] << '\n';
	}
	cout << '\n' << setw(40) << left << "Chebyshev nodes"
		<< setw(40) << left << "Function in Chebyshev nodes" << '\n' << '\n';
	for (int k = 0; k <= n; k++)
	{
		cout << setw(40) << left << ChebX[k]
			<< setw(40) << left << FuncInChebNodes[k] << '\n';
	}

	cout << '\n' << '\n' << "1) Lagrange Polynomial:" << '\n' << '\n';
	polynomialLagrange(equiX, FuncInEquiNodes, n);

	cout << '\n' << '\n' << "2) Newton Polynomial:" << '\n' << '\n';
	polynomialNewton(ChebX, FuncInChebNodes, n);

	cout << '\n' << '\n' << "3) Cubic Spline:" << '\n' << '\n';
	cubSpline(equiX, FuncInEquiNodes, h, n);

	cout << '\n' << '\n' << "4) Piecewise Linear Interpolation Function:" << '\n' << '\n';
	piecewiseLinInterpolFunc(equiX, FuncInEquiNodes, n);

	return 0;
}

