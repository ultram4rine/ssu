#include <iostream>

#include "functions.hpp"
#include "1Doptimization.hpp"
#include "ccd.hpp"
#include "rosenbrock.hpp"
#include "regular_simplex.hpp"
#include "random_search.hpp"

using namespace std;

int main()
{
     // epsilon for error.
     double eps = 1e-9;

     // target function.
     twoDFunc f = f15;

     // initial point.
     array<double, 2> x_0 = {-1, 1};

     array<double, 2> end_point1 = ccd(x_0, eps, f, golden_section_search);
     array<double, 2> end_point2 = rosenbrock(x_0, eps, f);
     array<double, 2> end_point3 = regular_simplex(x_0, eps, f);
     array<double, 2> end_point4 = random_search(x_0, eps, f);

     /*cout << "Value at initial point" << '\n';
     cout << f(x_0) << '\n';*/

     cout << "Coordinate Descent Method" << '\n'
          << '\n';
     cout << "(" << end_point1[0] << ", " << end_point1[1] << ")" << '\n';
     cout << f(end_point1) << '\n'
          << '\n';

     cout << "Rosenbrock Method" << '\n'
          << '\n';
     cout << "(" << end_point2[0] << ", " << end_point2[1] << ")" << '\n';
     cout << f(end_point2) << '\n'
          << '\n';

     cout << "Regular simplex method" << '\n'
          << '\n';
     cout << "(" << end_point3[0] << ", " << end_point3[1] << ")" << '\n';
     cout << f(end_point3) << '\n'
          << '\n';

          cout << "Random search method" << '\n'
          << '\n';
     cout << "(" << end_point4[0] << ", " << end_point4[1] << ")" << '\n';
     cout << f(end_point4) << '\n'
          << '\n';

     return 0;
}
