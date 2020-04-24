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
    array<double, 2> x_0 = { 0.5, 0.5 };

    //array<double, 2> end_point = coordinate_descent(x_0, eps, f2, inverse_quadratic_interpolation);

    array<double, 2> end_point = rosenbrock(x_0, eps, f1);

    // значение в начальной точке.
    cout << f1(x_0) << '\n';

    cout << "(" << end_point[0] << ", " << end_point[1] << ")" << '\n';

    cout << f1(end_point) << '\n';

    return 0;
}
