#include "1Doptimization.hpp"

#include <iostream>

// поиск интервала для метода золотого сечения.
array<double, 2> interval(twoDFunc f, int i, array<double, 2> init, double step)
{
	double d = 0.;

	// интервал.
	array<double, 2> ab = { 0,0 };

	ab[0] = init[i];
	double f_a = f(init);

	init[i] -= step;
	double f_dx = f(init);
	init[i] += step;

	if (f_dx < f_a)
		step = -step;

	init[i] += step;

	ab[1] = init[i];
	double f_b = f(init);

	while (f_b < f_a)
	{
		d = ab[0];
		ab[0] = ab[1];
		f_a = f_b;
		init[i] += step;
		ab[1] = init[i];
		f_b = f(init);
	}

	if (step < 0)
	{
		double c = ab[1];
		ab[1] = d;
		d = c;
	}

	ab[0] = d;

	return ab;
}

// обратная параболическая интерполяция.
double inverse_quadratic_interpolation(twoDFunc f, int i, array<double, 2> init, double eps)
{
	int n = 0;

	// нужны три точки.
	array<double, 2> xn_0 = init;
	array<double, 2> xn_1 = init;
	array<double, 2> xn_2 = init;

	array<double, 2> xnp = init;

	// смещаем крайние точки.
	xn_2[i] -= 0.3;
	xn_1[i] -= 0.15;

	double fn_1 = f(xn_1);
	double fn_2 = f(xn_2);

	while (fabs(xn_0[i] - xn_1[i]) > eps && n < 80)
	{
		double fn_0 = f(xn_0);

		double a = (fn_1 * fn_0) / ((fn_2 - fn_1) * (fn_2 - fn_0));
		double b = (fn_2 * fn_0) / ((fn_1 - fn_2) * (fn_1 - fn_0));
		double c = (fn_2 * fn_1) / ((fn_0 - fn_2) * (fn_0 - fn_1));

		xnp[i] = a * xn_2[i] + b * xn_1[i] + c * xn_0[i];

		xn_2[i] = xn_1[i];
		xn_1[i] = xn_0[i];
		xn_0[i] = xnp[i];

		fn_2 = fn_1;
		fn_1 = fn_0;

		n++;
	}

	init[i] = xnp[i];

	return init[i];
}

// последовательная параболическая интерполяция.
double sequential_quadratic_interpolation(twoDFunc f, int i, array<double, 2> init, double eps)
{
	int n = 0;

	// также нужны три точки.
	array<double, 2> xn_0 = init;
	array<double, 2> xn_1 = init;
	array<double, 2> xn_2 = init;

	array<double, 2> xnp = init;

	// также смещаем крайние точки.
	xn_2[i] -= 0.02;
	xn_1[i] -= 0.01;

	double fn_1 = f(xn_1);
	double fn_2 = f(xn_2);

	while (fabs(xn_0[i] - xn_1[i]) > eps && n < 200)
	{
		double fn_0 = f(xn_0);

		double v0 = xn_1[i] - xn_2[i];
		double v1 = xn_0[i] - xn_2[i];
		double v2 = xn_0[i] - xn_1[i];

		double s0 = xn_1[i] * xn_1[i] - xn_2[i] * xn_2[i];
		double s1 = xn_0[i] * xn_0[i] - xn_2[i] * xn_2[i];
		double s2 = xn_0[i] * xn_0[i] - xn_1[i] * xn_1[i];

		xnp[i] = 0.5 * (fn_2 * s2 - fn_1 * s1 + fn_0 * s0) / (fn_2 * v2 - fn_1 * v1 + fn_0 * v0);

		xn_2[i] = xn_1[i];
		xn_1[i] = xn_0[i];
		xn_0[i] = xnp[i];

		fn_2 = fn_1;
		fn_1 = fn_0;

		n++;
	}

	init[i] = xnp[i];

	return init[i];
}

// метод золотого сечения.
double golden_section_search(twoDFunc f, int i, array<double, 2> init, double eps)
{
	int n = 0;
	// золотое соотношение.
	double phi = (1 + sqrt(5)) / 2;
	// интервал.
	array<double, 2> ab = interval(f, i, init, 0.01);

	double a = ab[0];
	double b = ab[1];

	double x1 = b - (b - a) / phi;
	double x2 = a + (b - a) / phi;

	init[i] = x1;
	double f1 = f(init);
	init[i] = x2;
	double f2 = f(init);

	while ((b - a) / 2 > eps)
	{
		if (f1 > f2)
		{
			a = x1;
			x1 = x2;
			x2 = b - (x1 - a);

			init[i] = x1;
			f1 = f(init);
			init[i] = x2;
			f2 = f(init);
		}
		else
		{
			b = x2;
			x2 = x1;
			x1 = a + (b - x2);

			init[i] = x1;
			f1 = f(init);
			init[i] = x2;
			f2 = f(init);
		}
	}

	init[i] = (a + b) / 2;
	return init[i];
}
