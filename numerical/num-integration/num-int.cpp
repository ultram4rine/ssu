#include <iostream>
#include <cmath>

using namespace std;

//Function for Right Rectangles
void rightrectangle(double a, double b, int n, double h)
{
	double sum = 0;
	double *x = new double[n];
	double *f = new double[n];
	for (int i = 1; i <= n; i++)
	{
		x[i] = a + i * h;
		f[i] = h / (1 + (x[i] * x[i]));
		sum += f[i];
	}
	cout << "Sum for right rectangle: " << sum << '\n';
}

//Function for Left Rectangles
void leftrectangle(double a, double b, int n, double h)
{
	double sum = 0;
	double *x = new double[n];
	double *f = new double[n];
	for (int i = 0; i <= n - 1; i++)
	{
		x[i] = a + i * h;
		f[i] = h / (1 + (x[i] * x[i]));
		sum += f[i];
	}
	cout << "Sum for left rectangle: " << sum << '\n';
}

//Function for Centre Rectangles
void centrerectangle(double a, double b, int n, double h)
{
	double sum = 0;
	double *x = new double[n];
	double *f = new double[n];
	for (int i = 0; i <= n - 1; i++)
	{
		x[i] = a + i * h;
		f[i] = h / (1 + ((x[i] + (h / 2))*((x[i] + (h / 2)))));
		sum += f[i];
	}
	cout << "Sum for centre rectangle: " << sum << '\n';
}

//Function for Trapezium Method
void trapezium(double a, double b, int n, double h)
{
	double sum = 0, result = 0;
	double *x = new double[n];
	double *f = new double[n];
	x[0] = a + 0 * h;
	x[n] = a + n * h;
	f[0] = 1 / (1 + (x[0] * x[0]));
	f[n] = 1 / (1 + (x[n] * x[n]));
	for (int i = 1; i <= n - 1; i++)
	{
		x[i] = a + i * h;
		f[i] = 1 / (1 + (x[i] * x[i]));
		sum += f[i];
	}
	result = (h / 2)*(f[0] + f[n]) / 2 + h * sum;
	cout << "Sum for trapezium: " << result << '\n';
}

//Function for Simpson's Method
void simpson(double a, double b, int n, double h)
{
	int m = n / 2;
	double sum1 = 0, sum2 = 0, result = 0;
	double *x = new double[n];
	double *f = new double[n];
	x[0] = a + 0 * h;
	x[2 * m] = a + 2 * m * h;
	f[0] = 1 / (1 + (x[0] * x[0]));
	f[2 * m] = 1 / (1 + (x[2 * m] * x[2 * m]));
	for (int i = 1; i <= 2 * m - 1; i += 2)
	{
		x[i] = a + i * h;
		f[i] = 1 / (1 + (x[i] * x[i]));
		sum1 += f[i];
	}
	for (int i = 2; i <= 2 * m - 2; i += 2)
	{
		x[i] = a + i * h;
		f[i] = 1 / (1 + (x[i] * x[i]));
		sum2 += f[i];
	}
	result = h * (f[0] + f[2 * m] + 4 * sum1 + 2 * sum2) / 3;
	cout << "Sum for simpson: " << result << '\n';
}

//Function for Measure Error
void measError(double a, double b, int n, double h)
{
	double sum = 0, Rn, If;
	If = -atan(1) + atan(2);
	double *x = new double[n];
	double *f = new double[n];
	for (int i = 0; i <= n - 1; i++)
	{
		x[i] = a + i * h;
		f[i] = h / (1 + (x[i] * x[i]));
		sum += f[i];
	}
	Rn = abs(sum - If);
	cout << "Measure error: " << Rn << '\n';
}

int main() {
	double a = 1, b = 2;
	int n;
	cout << "Write n: ";
	cin >> n;
	double h = (b - a) / n;
	rightrectangle(a, b, n, h);
	leftrectangle(a, b, n, h);
	centrerectangle(a, b, n, h);
	trapezium(a, b, n, h);
	simpson(a, b, n, h);
	measError(a, b, n, h);
	return 0;
}
