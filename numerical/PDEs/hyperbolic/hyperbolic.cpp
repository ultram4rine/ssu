#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

/*double u(double a, double x_end, double k, double l, double x, double t)
{
    //double A = (2 * k * sin((M_PI * k) / l) * l * l) / (M_PI * l * l - M_PI * k * k);
    //double B = 2 * M_PI / k * (-((M_PI * pow(l, 4) - M_PI * k * pow(l, 3) - M_PI * k * k * l * l + M_PI * pow(k, 3) * l) * sin((M_PI * l + M_PI * k) / l) + (pow(l, 4) - 2 * k * pow(l, 3) + k * k * l * l) * cos((M_PI * l + M_PI * k) / l) + (-M_PI * pow(l, 4) - M_PI * k * pow(l, 3) + M_PI * k * k * l * l + M_PI * pow(k, 3) * l) * sin((M_PI * l - M_PI * k) / l) + (-pow(l, 4) - 2 * k * pow(l, 3) - k * k * l * l) * cos((M_PI * l - M_PI * k) / l)) / (2 * M_PI * M_PI * pow(l, 4) - 4 * M_PI * M_PI * k * k * l * l + 2 * M_PI * M_PI * pow(k, 4)) - (2 * k * pow(l, 3)) / (M_PI * M_PI * pow(l, 4) - 2 * M_PI * M_PI * k * k * l * l + M_PI * M_PI * pow(k, 4)));
    
    double A = 16 / (3 * M_PI);
    double B = 4 * (4 / (3 * M_PI) - 9 / (9 * M_PI * M_PI)) / M_PI;

    return (A * cos(M_PI) * a * t + B * sin(M_PI) * a * t) * sin(M_PI) * x;
}*/

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
    const double init_k = 2;
    const double init_l = 4;

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

    // count and fill table.
    for (auto j = 0; j <= t_size; j++)
    {
        std::cout << "| ";
        std::vector<double> row;
        row.push_back(boundary_start);
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
        }
        row.push_back(boundary_end);
        std::cout << std::left << std::setw(13) << row.at(x_size) << " | ";
        std::cout << '\n';
        table.push_back(row);
    }
    for (auto i = 0; i < 17.5 * x_size; i++)
    {
        char symbol = '-';
        if (i % 16 == 0)
            symbol = '+';
        std::cout << symbol;
    }
    std::cout << '\n';

    /*std::cout << "| ";
    for (auto i = 0; i <= x_size; i++)
    {
        std::cout << std::left << std::setw(13) << u(a, x_end, init_k, init_l, h * i, t_end) << " | ";
    }*/
}
