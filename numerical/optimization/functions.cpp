#include <cmath>

#include "functions.hpp"

double f1(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return pow((pow(x1, 2) + pow(x2, 2) - 1), 2) + pow((0.75 * pow(x1, 3) - 0.9 * pow(x2, 2) - 1), 2);
}

// функция Розенброка, глобальный минимум 0 в точке (1, 1).
double f2(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 100 * pow((x2 - pow(x1, 2)), 2) + pow((1 - x1), 2);
}

double f3(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return pow(pow(x1, 2) + x2 - 11, 2) + pow(x1 + pow(x2, 2) - 7, 2);
}
