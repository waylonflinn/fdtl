#include <limits>
#include "solver_basic.h"

solver_basic::solver_basic(int cutoff) : co(cutoff) {}

solver_basic::solver_basic() : co(std::numeric_limits<int>::max()) {}
