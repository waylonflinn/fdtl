#ifndef PDE_OPERATOR_RESTRICT
#define PDE_OPERATOR_RESTRICT
/* a restriction operator for use with multigrid algorithms */
#include "problem.h"
#include "boundary.h"

class operator_restrict
{
 public:
  virtual void operator()(const problem& fine, problem& coarse) = 0;
  virtual void operator()(const boundary& fine, boundary& coarse) = 0;
};
#endif	//PDE_OPERATOR_RESTRICT
