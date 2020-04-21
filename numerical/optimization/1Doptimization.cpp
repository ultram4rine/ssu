#include "1Doptimization.hpp"

#include <iostream>

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