#ifndef PDE_OPERATOR_PROLONG
#define PDE_OPERATOR_PROLONG
/* a prolongation operator for use with multigrid algorithms */
#include "problem.h"

class operator_prolong
{
 public:
  virtual void operator()(const problem& coarse, problem& fine) = 0;
};
#endif	//PDE_OPERATOR_PROLONG
