#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <array>

#include "ccd.hpp"

// Cyclic coordinate descent.
array<double, 2> ccd(array<double, 2> x_0, double eps, twoDFunc f, oneDoptimization odp)
{
    // step counter.
    int k = 0;
    // dimension of space.
    int n = x_0.size();

    double f_k = f(x_0);
    array<double, 2> x_k = x_0;
    double f_k1 = f(x_k);

    do
    {
        for (int i = 0; i < n; i++)
        {
            x_k[i] = odp(f, i, x_k, eps);
        }
        f_k = f_k1;
        f_k1 = f(x_k);

        k++;
    } while (fabs(f_k1 - f_k) > eps && k < 10000);

    cout << "Coordinate Descent Method" << '\n';
    cout << "iterations: " << k << '\n'
         << '\n';

    return x_k;
}
