/*
 * apply the gauss-seidel relaxation algorithm to a problem until
 * a specified goal is met or the cuttoff is reached.
 */
#include "goal.h"

class gauss_seidel
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

private:
  int cutoff;	// max iterations
};
