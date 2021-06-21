#include <array>

#include "functions.hpp"
#include "1Doptimization.hpp"

using namespace std;

array<double, 2> ccd(array<double, 2> x_0, double eps, twoDFunc f, oneDoptimization odm);