#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <array>

#include "rosenbrock.hpp"

// Rosenbrock method.
array<double, 2> rosenbrock(array<double, 2> x_0, double eps, twoDFunc f)
{
    // method parameters.
    double h0 = 0.5;
    array<double, 2> h = {h0, h0};
    double a = 3.0, b = -0.5;

    // step counter.
    int n = 0;

    // axis directions.
    array<double, 2> p1 = {1.0, 0.0}, p2 = {0.0, 1.0};
    array<array<double, 2>, 2> p = {p1, p2};

    double f_k = 0;
    double f_k1 = 0;

    array<double, 2> x_t = x_0;
    array<double, 2> x_k = x_0;
    array<double, 2> x_k1 = x_0;

    do
    {
        x_k = x_k1;
        x_t = x_k1;

        for (auto i = 0; i < 2; i++)
        {
            x_t[0] += h[i] * p[i][0];
            x_t[1] += h[i] * p[i][1];

            f_k = f(x_k1);
            f_k1 = f(x_t);

            if (f_k1 < f_k)
                h[i] *= a;
            else if (f_k1 > f_k)
                h[i] *= b;

            x_k1[0] += h[i] * p[i][0];
            x_k1[1] += h[i] * p[i][1];

            h[i] = h0;
        }

        f_k1 = f(x_k1);

        // build new coordinate system.
        p[0][0] = x_k1[0] - x_k[0];
        p[0][1] = x_k1[1] - x_k[1];

        p[1][0] = -p[0][1];
        p[1][1] = p[0][0];

        n++;
    } while (fabs(f_k1 - f_k) > eps && n < 10000);

    cout << "Rosenbrock Method" << '\n';
    cout << "iterations: " << n << '\n'
         << '\n';

    return x_k;
}
