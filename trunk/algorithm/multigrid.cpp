#include <limits>
#include "multigrid.h"

multigrid::multigrid(int max, int base, solver& smoother) : 
  co(max), mg(base), smooth(smoother) {}

multigrid::multigrid() :
  co(std::numeric_limits<int>::max()), mg(multigrid::DEF_BASE),
  def_smooth(1000), smooth(def_smooth) {}
