/* an adaptive linear multigrid system which uses nested iteration.
 * recursively applies a smoother to a problem on a series of coarser
 * grids until the goal is met. this process starts on a course
 * grid and is repreated on a series of finer grids, using the recursive
 * coarse solutions to constuct corrections, until the specified fineness
 * is reached.
 */
#include "solver.h"

class multigrid : public solver
{
public:
  // constants

  // constructors
  multigrid(int max, solver smoother);	// run for at most max iterations
  multigrid();	// any number of iterations, using gauss-seidel to smooth

  // methods

  // solve and return number of iters.
  int solve(problem& prob, goal& g);
  // synonym for solve
  int operator()(problem& prob, goal& g);

private:
  int cutoff;	// max iterations
  solver smooth;	// smoother
};
