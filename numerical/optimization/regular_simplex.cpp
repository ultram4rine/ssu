#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <array>
#include <utility>

#include "regular_simplex.hpp"

// Build regular simplex;
array<array<double, 2>, 3> build_simplex(array<double, 2> x_0, double l)
{
    int n = x_0.size();

    array<array<double, 2>, 3> nodes;
    nodes[0] = x_0;

    for (auto i = 1; i < n + 1; i++)
    {
        for (auto j = 0; j < n; j++)
        {
            nodes[i][j] = i == j + 1 ? nodes[0][j] + ((sqrt(n + 1) - 1) / (n * sqrt(2))) * l : nodes[0][j] + ((sqrt(n + 1) + n - 1) / (n * sqrt(2))) * l;
        }
    }

    return nodes;
}

// Reflect given node relatively to canter of mass.
array<double, 2> reflect_node(array<double, 2> x, array<array<double, 2>, 3> nodes)
{
    int n = x.size();

    array<double, 2> sum = {0, 0};

    for (auto i = 0; i < n; i++)
    {
        sum[0] += nodes[i][0];
        sum[1] += nodes[i][1];
    }
    sum[0] = sum[0] * 2 / n;
    sum[1] = sum[1] * 2 / n;
    sum[0] -= x[0];
    sum[1] -= x[1];

    return {sum[0], sum[1]};
}

// Regular simplex method.
array<double, 2> regular_simplex(array<double, 2> x_0, double eps, twoDFunc f)
{
    // step counter;
    int k = 0;
    // node counter;
    int d = 0;

    int n = x_0.size();

    // length of simplex edge.
    double l = 0.5;

    array<double, 2> x_1 = x_0;
    double f_2 = f(x_1);

    // build simplex.
    array<array<double, 2>, x_0.size() + 1> nodes = build_simplex(x_1, l);

    do
    {

        // sort.
        for (auto i = 0; i < n; i++)
        {
            int smallestIndex = i;

            for (int j = i + 1; j < n + 1; j++)
            {
                if (f(nodes[j]) < f(nodes[i]))
                    smallestIndex = j;
            }

            swap(nodes[i], nodes[smallestIndex]);
        }

        array<double, 2> x_2 = reflect_node(nodes[n], nodes);

        f_2 = f(x_2);
        if (f_2 < f(nodes[n]))
        {
            nodes[n] = x_2;
            d = 0;
        }
        else
        {
            if (1 + d > n)
            {
                break;
            }
            x_1 = nodes[n - (1 + d)];

            d++;
        }

        k++;
    } while (k < 1000);

    double sum_x1 = 0, sum_x2 = 0;
    for (auto i = 0; i < n + 1; i++)
    {
        sum_x1 += nodes[i][0];
        sum_x2 += nodes[i][1];
    }

    array<double, 2> center = {sum_x1 / 3, sum_x2 / 3};

    return center;
}
