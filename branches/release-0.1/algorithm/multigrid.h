/* an adaptive linear multigrid system which uses nested iteration with
 * bilinear interpolation for the prolongation operator and the standard
 * half weighting operator for restriction.
 * recursively applies a smoother to a problem on a series of coarser
 * grids until the goal is met. this process starts on a course
 * grid and is repreated on a series of finer grids, using the recursive
 * coarse solutions to constuct corrections, until the specified fineness
 * is reached.
 */
#include "gauss_seidel.h"

class multigrid
{
public:
  // constants

  // constructors
  multigrid(int max, solver& smoother);	// run for at most max iterations
  multigrid();	// any number of iterations, using gauss-seidel to smooth

  // methods

  // solve and return number of iters.
  template<class Problem> int solve(Problem& prob, goal& g);
  // synonym for solve
  template<class Problem> int operator()(Problem& prob, goal& g);

private:
  int cutoff;	// max iterations
  gauss_seidel def_smooth;
  solver& smooth;	// smoother

  template<class Problem> void mg(Problem& prob);
  template<class Problem> void pro(Problem& coarse, Problem& fine);
  template<class Problem> void rest(Problem& fine, Problem& coarse);
};
