#ifndef PDE_OPERATOR_PROLONG
#define PDE_OPERATOR_PROLONG
/* a prolongation operator for use with multigrid algorithms */
#include "problem.h"

class operator_prolong
{
  virtual problem operator()(problem& prob) = 0;
};
#endif	//PDE_OPERATOR_PROLONG
