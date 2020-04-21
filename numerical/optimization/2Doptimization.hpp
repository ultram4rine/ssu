#include <array>

#include "functions.hpp"
#include "1Doptimization.hpp"

using namespace std;

array<double, 2> coordinate_descent(array<double, 2> x_0, double eps, twoDFunc f, oneDoptimization odm);

array<double, 2> rosenbrock(array<double, 2> x_0, double q1, double q2, double eps, twoDFunc f);
