/* a partial implementation of the solver interface.
 */

#ifndef PDE_SOLVER_BASIC
#define PDE_SOLVER_BASIC

#include "solver.h"

class solver_basic
{
 public:
  // methods

  // set/get the maximum number of iterataions
  int& cutoff() {return co;}

 private:
  int co;

};

#endif	// PDE_SOLVER_BASIC
