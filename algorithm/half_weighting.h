#ifndef PDE_HALF_WEIGHTING
#define PDE_HALF_WEIGHTING

#include "operator_restrict.h"

class half_weighting : operator_restrict
{
  void operator()(const problem& fine, problem& coarse);
};

#endif	// PDE_HALF_WEIGHTING
