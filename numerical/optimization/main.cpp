#include <iostream>

#include "functions.hpp"
#include "1Doptimization.hpp"
#include "ccd.hpp"
#include "rosenbrock.hpp"
#include "regular_simplex.hpp"
#include "random_search.hpp"
#include "pattern_search.hpp"

using namespace std;

int main()
{
     // epsilon for error.
     double eps = 1e-9;

     // target function.
     twoDFunc f = f15;

     // initial point.
     array<double, 2> x_0 = {-1, 1};

     array<double, 2> min1 = ccd(x_0, eps, f, golden_section_search);
     array<double, 2> min2 = rosenbrock(x_0, eps, f);
     array<double, 2> min3 = regular_simplex(x_0, eps, f);
     array<double, 2> min4 = random_search(x_0, eps, f);
     array<double, 2> min5 = pattern_search(x_0, eps, f);

     /*cout << "Value at initial point" << '\n';
     cout << f(x_0) << '\n';*/

     cout << "Coordinate Descent Method" << '\n'
          << '\n';
     cout << "(" << min1[0] << ", " << min1[1] << ")" << '\n';
     cout << f(min1) << '\n'
          << '\n';

     cout << "Rosenbrock Method" << '\n'
          << '\n';
     cout << "(" << min2[0] << ", " << min2[1] << ")" << '\n';
     cout << f(min2) << '\n'
          << '\n';

     cout << "Regular simplex method" << '\n'
          << '\n';
     cout << "(" << min3[0] << ", " << min3[1] << ")" << '\n';
     cout << f(min3) << '\n'
          << '\n';

     cout << "Random search method" << '\n'
          << '\n';
     cout << "(" << min4[0] << ", " << min4[1] << ")" << '\n';
     cout << f(min4) << '\n'
          << '\n';

     cout << "Pattern search method" << '\n'
          << '\n';
     cout << "(" << min5[0] << ", " << min5[1] << ")" << '\n';
     cout << f(min5) << '\n'
          << '\n';

     return 0;
}
