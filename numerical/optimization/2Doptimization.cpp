#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "2Doptimization.hpp"

// метод покоординатного спуска.
array<double, 2> coordinate_descent(array<double, 2> x_0, double eps, twoDFunc f, oneDoptimization odp)
{
    int n = 0;

    double f_k = f(x_0);

    array<double, 2> x_k = x_0;
    double f_k1 = f(x_k);

    do
    {
        for (unsigned int i = 0; i < x_0.size(); i++)
        {
            x_k[i] = odp(f, i, x_k, eps);
        }
        f_k = f_k1;
        f_k1 = f(x_k);
        cout << "f0: " << f_k << '\n';
        cout << "f1: " << f_k1 << '\n' << '\n';
        n++;
    } while (fabs(f_k1 - f_k) > eps && n < 80);

    cout << "iterations: " << n << '\n' << '\n';

    return x_k;
}

// метод Розенброка.
array<double, 2> rosenbrock(double x1_0, double x2_0, double q1, double q2, double eps, twoDFunc f)
{
    return {0, 0};
}
