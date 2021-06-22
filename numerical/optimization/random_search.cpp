#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <array>
#include <utility>

#include "norm.hpp"
#include "random_search.hpp"

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

// Random search method.
array<double, 2> random_search(array<double, 2> x_0, double eps, twoDFunc f)
{
    int j = 0, M = 100;
    double alpha = 1, gamma = 2;
    array<double, 2> x = x_0;

    do
    {
        array<double, 2> xi = {fRand(-1, 1), fRand(-1, 1)};

        array<double, 2> y = {x_0[0] + alpha * (xi[0] / norm(xi)), x_0[1] + alpha * (xi[1] / norm(xi))};

        if (f(y) < f(x))
        {
            x = y;
        }
        else
        {
            j++;
            if (j < M)
            {
                alpha /= gamma;
                j = 0;
            }
        }
    } while (alpha > eps);

    return x;
}