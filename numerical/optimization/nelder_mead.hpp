#include <array>

#include "functions.hpp"

using namespace std;

array<double, 2> nelder_mead(array<double, 2> x_0, double eps, twoDFunc f);