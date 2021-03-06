﻿#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>

double u(double x, double t)
{
    return (cos(M_PI * t) + 1 / (2 * M_PI) * sin(M_PI * t)) * sin(M_PI * x);
}

double initial_u(double k, double l, double x)
{
    return k * sin((k * M_PI * x) / l);
}

double initial_ut(double k, double l, double x)
{
    return k * x * sin((k * M_PI * x) / l);
}

int main()
{
    const double boundary_start = 0;
    const double boundary_end = 0;

    // variables for initial functions.
    const double init_k = 1;
    const double init_l = 1;

    const double x_start = 0.;
    const double x_end = 1.;

    const double t_start = 0.;
    const double t_end = 0.2;

    const double a = 1.;

    const double h = .125;
    const double l = .025;

    const double alpha = (a * l) / h;
    std::cout << alpha << '\n';
    if (alpha <= 1.)
        std::cout << "alpha is good" << '\n' << '\n';
    else
        std::cout << "alpha is bad" << '\n' << '\n';

    int x_size = fabs(x_end - x_start) / h;
    int t_size = fabs(t_end - t_start) / l;

    std::vector<std::vector<double>> table;

    std::cout << "| ";
    for (auto i = 0; i <= x_size; i++)
    {
        std::cout << std::left << std::setw(13) << i << " | ";
    }
    std::cout << '\n';
    for (auto i = 0; i < 17.5 * x_size; i++)
    {
        char symbol = '-';
        if (i % 16 == 0)
            symbol = '+';
        std::cout << symbol;
    }
    std::cout << '\n';

    std::cout << "| ";
    for (auto i = 0; i <= x_size; i++)
    {
        std::cout << std::left << std::setw(13) << h * i << " | ";
    }
    std::cout << '\n';
    for (auto i = 0; i < 17.5 * x_size; i++)
    {
        char symbol = '-';
        if (i % 16 == 0)
            symbol = '+';
        std::cout << symbol;
    }
    std::cout << '\n';

    std::ofstream csv;
    csv.open("hyperbolic.csv");
    csv << "# X Y Z\n";

    // count and fill table.
    for (auto j = 0; j <= t_size; j++)
    {
        std::cout << "| ";
        std::vector<double> row;
        row.push_back(boundary_start);
        csv << 0 << "," << l * j << "," << row.at(0) << "\n";
        std::cout << std::left << std::setw(13) << row.at(0) << " | ";
        for (auto i = 1; i < x_size; i++)
        {
            if (j == 0)
            {
                row.push_back(initial_u(init_k, init_l, h * i));
            }
            else if (j == 1)
            {
                row.push_back(1 / 2 * (initial_u(init_k, init_l, h * (i + 1)) + initial_u(init_k, init_l, h * (i - 1))) + l * initial_ut(init_k, init_l, h * i));
            }
            else
            {
                row.push_back(alpha * alpha * table.at(j - 1).at(i + 1) - 2 * table.at(j - 1).at(i) * (alpha * alpha - 1) + alpha * alpha * table.at(j - 1).at(i - 1) - table.at(j - 2).at(i));
            }
            std::cout << std::left << std::setw(13) << row.at(i) << " | ";
            csv << h * i << "," << l * j << "," << row.at(i) << "\n";
        }
        row.push_back(boundary_end);
        std::cout << std::left << std::setw(13) << row.at(x_size) << " | ";
        csv << h * x_size << "," << l * j << "," << row.at(x_size) << '\n' << '\n';
        std::cout << '\n';
        table.push_back(row);
    }

    std::cout << "| ";
    for (auto i = 0; i <= x_size; i++)
        std::cout << std::left << std::setw(13) << u(h * i, t_end) << " | ";
    std::cout << '\n';

    for (auto i = 0; i < 17.5 * x_size; i++)
    {
        char symbol = '-';
        if (i % 16 == 0)
            symbol = '+';
        std::cout << symbol;
    }
    std::cout << '\n';

    csv.close();
}
