/* a partial implementation of the solver interface.
 */

#ifndef PDE_SOLVER_BASIC
#define PDE_SOLVER_BASIC

#include "solver.h"

class solver_basic : public solver
{
 public:
  /// methods

  // set/get the maximum number of iterataions
  int& cutoff() {return co;}

  /// constructors

  solver_basic(int cutoff);
  /* run for the number of iterations equal to the largest 'int' representable
   * on the target architecture.
   */
  solver_basic();

 protected:
  int co;

};

#endif	// PDE_SOLVER_BASIC
