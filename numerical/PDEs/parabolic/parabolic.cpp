#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>

double initial_condition(double x)
{
    return (1.1 * x * x + 2.1) * pow(M_E, -x);
}

int main()
{
    const double boundary_start = 2.1;
    const double boundary_end = 3.2 * pow(M_E, -1);

    const double x_start = 0.;
    const double x_end = 1.;

    const double t_start = 0.;
    const double t_end = 0.01;

    const double a = 1.;

    const double h = .0625;
    const double l = .000625;

    const double sigma = (a * a * l) / (h * h);
    std::cout << sigma << '\n';
    if (sigma > 0 && sigma <= 0.5)
        std::cout << "sigma is good" << '\n' << '\n';
    else
        std::cout << "sigma is bad" << '\n' << '\n';

    int x_size = fabs(x_end - x_start) / h;
    int t_size = fabs(t_end - t_start) / l;

    std::vector<std::vector<double>> table;

    std::cout << "| ";
    for (auto i = 0; i <= x_size; i++)
    {
        std::cout << std::left << std::setw(8) << i << " | ";
    }
    std::cout << '\n';
    for (auto i = 0; i < 12.5 * x_size; i++)
    {
        char symbol = '-';
        if (i % 11 == 0)
            symbol = '+';
        std::cout << symbol;
    }
    std::cout << '\n';
    
    std::cout << "| ";
    for (auto i = 0; i <= x_size; i++)
    {
        std::cout << std::left << std::setw(8) << h * i << " | ";
    }
    std::cout << '\n';
    for (auto i = 0; i < 12.5 * x_size; i++)
    {
        char symbol = '-';
        if (i % 11 == 0)
            symbol = '+';
        std::cout << symbol;
    }
    std::cout << '\n';

    std::ofstream csv;
    csv.open("parabolic.csv");
    csv << "# X Y Z\n";

    // count and fill table and csv file.
    for (auto j = 0; j <= t_size; j++)
    {
        std::cout << "| ";
        std::vector<double> row;
        row.push_back(boundary_start);
        std::cout << std::left << std::setw(8) << row.at(0) << " | ";
        csv << 0 << "," << l * j << "," << row.at(0) << "\n";
        for (auto i = 1; i < x_size; i++)
        {
            if (j == 0)
            {
                row.push_back(initial_condition(h * i));
                //std::cout << h*i << ":" << initial_condition(h * i) << '\n';
            }
            else
            {
                row.push_back(sigma * table.at(j - 1).at(i + 1) - table.at(j - 1).at(i) * (2 * sigma - 1) + sigma * table.at(j - 1).at(i - 1));
            }
            std::cout << std::left << std::setw(8) << row.at(i) << " | ";
            csv << h * i << "," << l * j << "," << row.at(i) << "\n";
        }
        row.push_back(boundary_end);
        std::cout << std::left << std::setw(8) << row.at(x_size) << " | ";
        csv << h * x_size << "," << l * j << "," << row.at(x_size) << "\n";
        std::cout << '\n';
        table.push_back(row);
    }
    std::cout << '\n';

    csv.close();
}
