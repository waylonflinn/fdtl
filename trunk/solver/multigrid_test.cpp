#include <limits>
#include "multigrid.h"

multigrid::multigrid(int max, int base, solver& smoother) : 
  init(false), co(max), mg(base), smooth(smoother) {}

multigrid::multigrid() :
  init(false), co(std::numeric_limits<int>::max()), mg(multigrid::DEF_BASE),
  def_smooth(1000), smooth(def_smooth) {}
