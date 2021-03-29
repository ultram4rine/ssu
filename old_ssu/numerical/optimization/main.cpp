#include <iostream>

#include "functions.hpp"
#include "1Doptimization.hpp"
#include "2Doptimization.hpp"

using namespace std;

int main()
{
    // точность метода.
    double eps = 1e-9;

    // целевая функция.
    twoDFunc f = f1;

    // начальное приближение.
    array<double, 2> x_0 = { 0.5, 0.5 };

    array<double, 2> end_point1 = coordinate_descent(x_0, eps, f, inverse_quadratic_interpolation);
    array<double, 2> end_point2 = coordinate_descent(x_0, eps, f, sequential_quadratic_interpolation);
    array<double, 2> end_point3 = coordinate_descent(x_0, eps, f, golden_section_search);

    array<double, 2> end_point4 = rosenbrock(x_0, eps, f);

    // значение в начальной точке.
    cout << "Value at initial point" << '\n';
    cout << f(x_0) << '\n';

    cout << "Coordinate Descent Method" << '\n' << '\n';

    cout << "inverse quadratic interpolation as 1 dimential optimization" << '\n';
    cout << "(" << end_point1[0] << ", " << end_point1[1] << ")" << '\n';
    cout << f(end_point1) << '\n' << '\n';

    cout << "sequential quadratic interpolation as 1 dimential optimization" << '\n';
    cout << "(" << end_point2[0] << ", " << end_point2[1] << ")" << '\n';
    cout << f(end_point2) << '\n' << '\n';

    cout << "golden section search as 1 dimential optimization" << '\n';
    cout << "(" << end_point3[0] << ", " << end_point3[1] << ")" << '\n';
    cout << f(end_point3) << '\n' << '\n';

    cout << "Rosenbrock Method" << '\n' << '\n';

    cout << "(" << end_point4[0] << ", " << end_point4[1] << ")" << '\n';
    cout << f(end_point4) << '\n' << '\n';

    return 0;
}
