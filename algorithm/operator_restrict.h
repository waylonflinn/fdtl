#ifndef PDE_OPERATOR_RESTRICT
#define PDE_OPERATOR_RESTRICT
/* a restriction operator for use with multigrid algorithms */
#include "problem.h"

class operator_restrict
{
  virtual problem operator()(problem& prob) = 0;
};
#endif	//PDE_OPERATOR_RESTRICT
