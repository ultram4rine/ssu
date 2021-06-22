#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <array>
#include <utility>

#include "norm.hpp"
#include "pattern_search.hpp"

// Helper.
array<double, 2> coordinate_descent(array<double, 2> x, array<double, 2> h, twoDFunc f)
{
    array<double, 2> x_0 = x;

    for (auto j = 0; j < x_0.size(); j++)
    {
        array<double, 2> y = x_0;
        y[j] -= h[j];
        if (f(x) <= f(y))
        {
            y = x_0;
            y[j] += h[j];
            if (f(x) <= f(y))
            {
                continue;
            }
            else
            {
                x_0 = y;
            }
        }
        else
        {
            x_0 = y;
        }
    }

    return x_0;
}

// Pattern search method.
array<double, 2> pattern_search(array<double, 2> x_0, double eps, twoDFunc f)
{
    array<double, 2> x_1 = x_0;
    array<double, 2> h = {1, 1};
    double gamma = 2;

    int k = 0;

    do
    {
        array<double, 2> x = coordinate_descent(x_1, h, f);
        if (x[0] != x_1[0] || x[1] != x_1[1])
        {
            array<double, 2> x_2 = {2 * x[0] - x_1[0], 2 * x[1] - x_1[1]};
            x_1 = x_2;
        }
        for (auto i = 0; i < 2; i++)
        {
            h[i] /= gamma;
        }
        k++;
    } while (norm(h) > eps && k < 100);

    return x_1;
}
