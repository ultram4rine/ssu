#include <array>

#include "functions.hpp"

using namespace std;

typedef double oneDoptimization(twoDFunc f, int i, array<double, 2> init, double eps);

// обратна€ параболическа€ интерпол€ци€.
double inverse_quadratic_interpolation(twoDFunc f, int i, array<double, 2> init, double eps);

// последовательна€ параболическа€ интерпол€ци€.
double sequential_quadratic_interpolation(twoDFunc f, int i, array<double, 2> init, double eps);

double golden_section_search(twoDFunc f, int i, array<double, 2> init, double eps);