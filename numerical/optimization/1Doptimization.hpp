#include <array>

#include "functions.hpp"

using namespace std;

typedef double oneDoptimization(twoDFunc f, int i, array<double, 2> init, double eps);

double inverse_quadratic_interpolation(twoDFunc f, int i, array<double, 2> init, double eps);
