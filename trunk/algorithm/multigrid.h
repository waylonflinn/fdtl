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
#include "solver_basic.h"
#include <utility>

using std::pair;

class multigrid : solver_basic
{
public:
  // constants

  // constructors
  multigrid(int max, solver& smoother);	// run for at most max iterations
  multigrid();	// any number of iterations, using gauss-seidel to smooth

  // methods

  // solve and return number of iters.
  int solve(problem_resizable& prob, goal& g);
  // synonym for solve
  int operator()(problem_resizable& prob, goal& g);

private:
  gauss_seidel def_smooth;
  solver& smooth;	// smoother

  void prolong(problem& coarse, problem& fine);
  void restrict(problem& fine, problem& coarse);
};
