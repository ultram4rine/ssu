#include <iostream>

#include "functions.hpp"
#include "1Doptimization.hpp"
#include "2Doptimization.hpp"

using namespace std;

int main()
{
    // точность метода.
    double eps = 1e-5;

    // начальное приближение.
    array<double, 2> x_0 = { 10, 10 };

    array<double, 2> end_point = coordinate_descent(x_0, eps, f3, inverse_quadratic_interpolation);

    cout << "(" << end_point[0] << ", " << end_point[1] << ")" << '\n';

    cout << f3(end_point) << '\n';

    return 0;
}
