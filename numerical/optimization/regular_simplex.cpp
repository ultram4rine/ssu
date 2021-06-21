#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <array>
#include <utility>

#include "regular_simplex.hpp"

// Regular simplex method.
array<double, 2> regular_simplex(array<double, 2> x_0, double eps, twoDFunc f)
{
    // step counter;
    int k = 0;

    int n = x_0.size();

    array<double, 2> x_1 = x_0;
    double f_2 = f(x_1);
    array<array<double, 2>, x_0.size() + 1> nodes = build_simplex(x_1, f);

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

        for (auto i = 0; i < n + 1; i++)
        {
            cout << nodes[i][0] << " " << nodes[i][1] << ": " << f(nodes[i]) << '\n';
        }

        array<double, 2> x_2 = reflect_node(nodes[n], nodes);

        cout << "reflected: " << x_2[0] << " " << x_2[1] << '\n';

        f_2 = f(x_2);
        cout << "f(x_2): " << f_2 << " f(x_1) " << f(nodes[n]) << '\n';
        if (f_2 < f(nodes[n]))
        {
            cout << "next" << '\n';
            nodes[n] = x_2;
        }
        else
        {
            cout << "prev" << '\n';
            if (1 + k > n)
            {
                break;
            }
            x_1 = nodes[n - (1 + k)];
            cout << x_1[0] << " " << x_1[1] << '\n'
                 << '\n';

            k++;
        }

    } while (/*fabs(f_2 - f(nodes[n])) > eps &&*/ k < 10);

    return nodes[0];
}

array<array<double, 2>, 3> build_simplex(array<double, 2> x_0, twoDFunc f)
{
    // length of simplex edge.
    int l = 1;
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
    sum[0] -= nodes[n][0];
    sum[1] -= nodes[n][1];

    return {sum[0], sum[1]};
}
