#include <cmath>
#include <array>

#include "norm.hpp"

using namespace std;

double norm(array<double, 2> x)
{
    double sum = 0;
    for (auto i = 0; i < 2; i++)
    {
        sum += x[i];
    }
    return sqrt(sum);
}
