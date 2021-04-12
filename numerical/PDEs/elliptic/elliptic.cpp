#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>

double x_0(double y)
{
    return 30 * sin(M_PI * y);
}

double x_1(double y)
{
    return 20 * (1 - y);
}

double y_0(double x)
{
    return 20 * x;
}

double y_1(double x)
{
    return 30 * x * (1 - x);
}

int main()
{
    const double x_start = 0.;
    const double x_end = 1.;

    const double y_start = 0.;
    const double y_end = 1.;

    const double h = .125;
    const double l = .125;

    int x_size = fabs(x_end - x_start) / h;
    int y_size = fabs(y_end - y_start) / l;

	std::ofstream csv_start, csv_end;
	csv_start.open("elliptic_start.csv");
    csv_end.open("elliptic_end.csv");
	csv_start << "# X Y Z\n";
    csv_end << "# X Y Z\n";

    std::vector<std::vector<double>> grid;
    
    // fill the grid by initial approximation.
    for (auto j = y_size; j >= 0; j--)
    {
        std::vector<double> row;
        for (auto i = 0; i <= x_size; i++)
        {
            if (j == 0)
                row.push_back(y_0(h * i));
            else if (j == y_size)
                row.push_back(y_1(h * i));
            else if (i == 0)
                row.push_back(x_0(l * j));
            else if (i == x_size)
                row.push_back(x_1(l * j));
            else
            {
                if (x_0(l * j) < x_1(l * j))
                    row.push_back(x_0(l * j) / (x_size + 1) * i);
                else if (x_0(l * j) > x_1(l * j))
                    row.push_back(x_1(l * j) / (x_size + 1) * (x_size + 1 - i));
                else
                    row.push_back(x_0(l * j));
            }
            std::cout << std::left << std::setw(8) << row.at(i) << " | ";
            csv_start << h * i << "," << l * (y_size - j) << "," << row.at(i) << "\n";
        }
        csv_start << '\n';
        std::cout << '\n';
        grid.push_back(row);
    }
    std::cout << '\n';

    csv_start.close();

    int n = 0;
    double max_diff = -1;
    // iterative process.
    do
    {
        max_diff = -1;
        for (auto j = 1; j < y_size; j++)
        {
            for (auto i = 1; i < x_size; i++)
            {
                double old_value = grid.at(j).at(i);
                grid.at(j).at(i) = 1. / 4. * (grid.at(j).at(i + 1) + grid.at(j).at(i - 1) + grid.at(j + 1).at(i) + grid.at(j - 1).at(i));
                if (fabs(grid.at(j).at(i) - old_value) > max_diff)
                    max_diff = fabs(grid.at(j).at(i) - old_value);
            }
        }
        n++;
    } while (max_diff > DBL_EPSILON);
    std::cout << n << '\n';

    // cout.
    for (auto j = 0; j <= y_size; j++)
    {
        for (auto i = 0; i <= x_size; i++)
        {
            std::cout << std::left << std::setw(8) << grid.at(j).at(i) << " | ";
            csv_end << h * i << "," << l * j << "," << grid.at(j).at(i) << "\n";
        }
        csv_end << '\n';
        std::cout << '\n';
    }
    std::cout << '\n';

    csv_end.close();
}
