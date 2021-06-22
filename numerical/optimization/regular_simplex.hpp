#include <array>

#include "functions.hpp"

using namespace std;

array<double, 2> regular_simplex(array<double, 2> x_0, double eps, twoDFunc f);

array<array<double, 2>, 3> build_simplex(array<double, 2> x_0, double l);

array<double, 2> reflect_node(array<double, 2> x, array<array<double, 2>, 3> nodes);
