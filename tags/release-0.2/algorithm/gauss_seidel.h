/*
 * apply the gauss-seidel relaxation algorithm to a problem until
 * a specified goal is met or the cuttoff is reached.
 */
#ifndef PDE_GAUSS_SEIDEL
#define PDE_GAUSS_SEIDEL

#include "solver_basic.h"

class gauss_seidel : public solver_basic
{
public:
  // constants

  // constructors
  gauss_seidel(int max);	// run for at most max iterations
  gauss_seidel();		// place no limits on the number of iterations

  // methods

  // solve and return number of iters.
  int solve(problem& prob, goal& g);
  // synonym for solve
  int operator()(problem& prob, goal& g);
};

#endif	// PDE_GAUSS_SEIDEL
