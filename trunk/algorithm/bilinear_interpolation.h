#ifndef PDE_BILINEAR_INTERPOLATION
#define PDE_BILINEAR_INTERPOLATION

#include "operator_prolong.h"

class bilinear_interpolation : operator_prolong
{
 public:
  void operator()(const problem& coarse, problem& fine);
};

#endif	// PDE_BILINEAR_INTERPOLATION
