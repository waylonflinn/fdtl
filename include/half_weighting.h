#ifndef PDE_HALF_WEIGHTING
#define PDE_HALF_WEIGHTING

#include "operator_restrict.h"

class half_weighting : public operator_restrict
{
 public:
  void operator()(const problem& fine, problem& coarse);
  void operator()(const boundary& fine, boundary& coarse);
};

#endif	// PDE_HALF_WEIGHTING
