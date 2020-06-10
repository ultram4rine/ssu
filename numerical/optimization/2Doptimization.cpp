#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "2Doptimization.hpp"

// метод покоординатного спуска.
array<double, 2> coordinate_descent(array<double, 2> x_0, double eps, twoDFunc f, oneDoptimization odp)
{
    // счетчик шагов.
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
    cout << "iterations: " << n << '\n' << '\n';

    return x_k;
}

// метод Розенброка.
array<double, 2> rosenbrock(array<double, 2> x_0, double eps, twoDFunc f)
{
    // параметры метода.
    double h0 = 0.5;
    array<double, 2> h = { h0, h0 };
    double a = 3.0, b = -0.5;

    // счетчик шагов.
    int n = 0;

    // направления осей.
    array<double, 2> p1 = { 1.0, 0.0 }, p2 = { 0.0, 1.0 };
    array<array<double, 2>, 2> p = { p1, p2 };

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

        // строим новую систему координат.
        p[0][0] = x_k1[0] - x_k[0];
        p[0][1] = x_k1[1] - x_k[1];

        p[1][0] = -p[0][1];
        p[1][1] = p[0][0];

        n++;
    } while (fabs(f_k1 - f_k) > eps && n < 10000);

    cout << "Rosenbrock Method" << '\n';
    cout << "iterations: " << n << '\n' << '\n';

    return x_k;
}
