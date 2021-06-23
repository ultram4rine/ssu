#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <array>
#include <utility>

#include "nelder_mead.hpp"

// Nelder-Mead method.
array<double, 2> nelder_mead(array<double, 2> x_0, double eps, twoDFunc f)
{
    // length of simplex;
    double l = 2;

    // parameters.
    double alpha = 1, beta = 0.5, gamma = 2;

    int n = x_0.size();

    array<double, 2> x = x_0;

    // build simplex;
    array<array<double, 2>, 3> nodes;
    for (int i = 1; i <= n + 1; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i - 1)
            {
                nodes[i - 1][j - 1] = x[j - 1];
            }
            else if (j == i - 1)
            {
                nodes[i - 1][j - 1] = x[j - 1] + sqrt((double)j / (2 * ((double)j + 1))) * l;
            }
            else
            {
                nodes[i - 1][j - 1] = x[j - 1] - l / sqrt(2 * j * (j + 1));
            }
        }
    }

    int k = 0;

    while (k < 1000)
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

        array<double, 2> x_h = nodes[2], x_g = nodes[1], x_l = nodes[0];

        // reflect node.
        array<double, 2> sum = {0, 0};
        for (auto i = 0; i < n; i++)
        {
            sum[0] += nodes[i][0];
            sum[1] += nodes[i][1];
        }
        sum[0] = sum[0] / n;
        sum[1] = sum[1] / n;

        array<double, 2> x_r = {(1 + alpha) * sum[0] - alpha * nodes[2][0], (1 + alpha) * sum[1] - alpha * nodes[2][1]};

        x = x_r;

        double f_r = f(x_r), f_h = f(x_h), f_g = f(x_g), f_l = f(x_l);

        k++;

        if (f_r < f_l)
        {
            array<double, 2> x_e = {(1 - gamma) * sum[0] + gamma * x_r[0], (1 - gamma) * sum[1] + gamma * x_r[1]};
            double f_e = f(x_e);
            if (f_e < f_r)
            {
                nodes[2] = x_e;
            }
            else
            {
                nodes[2] = x_r;
            }
        }
        else if (f_l < f_r && f_r < f_g)
        {
            nodes[2] = x_r;
        }
        else if (f_g < f_r && f_r < f_h)
        {
            array<double, 2> tmp = nodes[2];
            nodes[2] = x_r;
            x_r = tmp;

            array<double, 2> x_s = {beta * x_h[0] + (1 - beta) * sum[0], beta * x_h[1] + (1 - beta) * sum[1]};
            double f_s = f(x_s);
            if (f_s < f_h)
            {
                nodes[2] = x_s;
            }
            else
            {
                nodes[2] = {x_l[0] + (x_h[0] - x_l[0]) / 2, x_l[1] + (x_h[1] - x_l[1]) / 2};
                nodes[1] = {x_l[0] + (x_g[0] - x_l[0]) / 2, x_l[1] + (x_g[1] - x_l[1]) / 2};
            }
        }
        else if (f_h < f_r)
        {
            array<double, 2> x_s = {beta * x_h[0] + (1 - beta) * sum[0], beta * x_h[1] + (1 - beta) * sum[1]};
            double f_s = f(x_s);
            if (f_s < f_h)
            {
                nodes[2] = x_s;
            }
            else
            {
                nodes[2] = {x_l[0] + (x_h[0] - x_l[0]) / 2, x_l[1] + (x_h[1] - x_l[1]) / 2};
                nodes[1] = {x_l[0] + (x_g[0] - x_l[0]) / 2, x_l[1] + (x_g[1] - x_l[1]) / 2};
            }
        }

        double disp = 0;
        for (int i = 0; i < n; i++)
        {
            disp += pow(nodes[i][0] - nodes[n][0], 2);
            disp += pow(nodes[i][1] - nodes[n][1], 2);
        }
        disp /= 2;

        if (disp < eps)
        {
            break;
        }
    };

    return x;
}