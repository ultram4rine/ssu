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
        cout << "f0: " << f_k << '\n';
        cout << "f1: " << f_k1 << '\n' << '\n';
        n++;
    } while (fabs(f_k1 - f_k) > eps && n < 80);

    cout << "iterations: " << n << '\n' << '\n';

    return x_k;
}

// метод Розенброка.
array<double, 2> rosenbrock(array<double, 2> x_0, double eps, twoDFunc f)
{
    // параметры метода.
    double h0 = 0.5, h = h0;
    double a = 3, b = -0.5;

    // счетчик шагов.
    int n = 0;

    // направления осей.
    array<double, 2> p1 = { 1,0 }, p2 = { 0,1 };

    double f_k = f(x_0);

    array<double, 2> x_k = x_0;
    double f_k1 = f(x_k);

    do
    {
        x_0 = x_k;

        // пробный шаг по первой координате.
        x_k[0] += h * p1[0];
        x_k[1] += h * p1[1];

        f_k = f_k1;
        f_k1 = f(x_k);

        // вернулись.
        x_k[0] -= h * p1[0];
        x_k[1] -= h * p1[1];
        f_k = f(x_k);

        cout << "first coordinate" << '\n';
        cout << "f0: " << f_k << '\n';
        cout << "f1: " << f_k1 << '\n' << '\n';

        if (f_k1 < f_k)
            h *= a;
        else if (f_k1 > f_k)
            h *= b;

        // шагнули.
        x_k[0] += h * p1[0];
        x_k[1] += h * p1[1];
        f_k1 = f(x_k);

        // восстанавливаем h а то он может слишком дохера шагнуть.
        h = h0;

        // повторяем процесс для второй координаты.
        x_k[0] += h * p2[0];
        x_k[1] += h * p2[1];

        f_k = f_k1;
        f_k1 = f(x_k);

        x_k[0] -= h * p2[0];
        x_k[1] -= h * p2[1];
        f_k = f(x_k);

        cout << "second coordinate" << '\n';
        cout << "f0: " << f_k << '\n';
        cout << "f1: " << f_k1 << '\n' << '\n';

        if (f_k1 < f_k)
            h *= a;
        else if (f_k1 > f_k)
            h *= b;

        x_k[0] += h * p2[0];
        x_k[1] += h * p2[1];
        f_k1 = f(x_k);

        // строим новую систему координат.
        p1[0] = x_k[0] - x_0[0];
        p1[1] = x_k[1] - x_0[1];

        p2[0] = -p1[1];
        p2[1] = p1[0];

        n++;
    } while (fabs(f_k1 - f_k) > eps && n < 80);

    cout << "iterations: " << n << '\n' << '\n';

    return x_k;
}
