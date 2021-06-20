#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <array>

#include "coordinate_descent.hpp"

// Coordinate descent.
array<double, 2> coordinate_descent(array<double, 2> x_0, double eps, twoDFunc f, oneDoptimization odp)
{
    // step counter.
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

        n++;
    } while (fabs(f_k1 - f_k) > eps && n < 10000);

    cout << "Coordinate Descent Method" << '\n';
    cout << "iterations: " << n << '\n'
         << '\n';

    return x_k;
}