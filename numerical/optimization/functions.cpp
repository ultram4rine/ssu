#include <cmath>

#include "functions.hpp"

double f1(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 32 * pow(x1, 2) + 63 * x1 * x2 + 32 * pow(x2, 2) - 5 * x1 + 15 * x2 + 6;
}

double f2(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 60 * pow(x1, 2) - 128 * x1 * x2 + 60 * pow(x2, 2) - 25 * x1 - 75 * x2 + 14;
}

double f3(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 127 * pow(x1, 2) + 253 * x1 * x2 + 127 * pow(x2, 2) + 25 * x1 + 65 * x2 - 16;
}

double f4(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 75 * pow(x1, 2) - 150 * x1 * x2 + 75 * pow(x2, 2) - 17 * x1 + 50 * x2 + 24;
}

double f5(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 43 * pow(x1, 2) + 84 * x1 * x2 + 43 * pow(x2, 2) + 15 * x1 - 26 * x2 + 42;
}

double f6(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 105 * pow(x1, 2) - 210 * x1 * x2 + 105 * pow(x2, 2) - 96 * x1 + 25 * x2 - 13;
}

double f7(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 97 * pow(x1, 2) + 188 * x1 * x2 + 97 * pow(x2, 2) + 15 * x1 - 115 * x2 + 2;
}

double f8(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 23 * pow(x1, 2) - 44 * x1 * x2 + 23 * pow(x2, 2) + 51 * x1 + 134 * x2 - 5;
}

double f9(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 50 * pow(x1, 2) + 98 * x1 * x2 + 50 * pow(x2, 2) - 47 * x1 - 4 * x2 + 45;
}

double f10(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 32 * pow(x1, 2) + 63 * x1 * x2 + 32 * pow(x2, 2) - 5 * x1 + 15 * x2 + 6;
}

double f11(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 76 * pow(x1, 2) - 141 * x1 * x2 + 76 * pow(x2, 2) - 17 * x1 + 49 * x2 + 14;
}

double f12(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 103 * pow(x1, 2) - 105 * x1 * x2 + 103 * pow(x2, 2) - 76 * x1 + 27 * x2 - 21;
}

double f13(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 33 * pow(x1, 2) + 53 * x1 * x2 + 33 * pow(x2, 2) - 6 * x1 + 17 * x2 + 7;
}

double f14(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 48 * pow(x1, 2) + 78 * x1 * x2 + 48 * pow(x2, 2) - 37 * x1 - 7 * x2 + 4;
}

double f15(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 93 * pow(x1, 2) + 157 * x1 * x2 + 93 * pow(x2, 2) + 14 * x1 - 111 * x2 + 19;
}

double f16(array<double, 2> x)
{
    double x1 = x[0];
    double x2 = x[1];
    return 59 * pow(x1, 2) - 118 * x1 * x2 + 59 * pow(x2, 2) - 22 * x1 - 77 * x2 + 13;
}
