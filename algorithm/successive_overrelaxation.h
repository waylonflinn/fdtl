/*
 * apply the successive overrelaxation algorithm to a problem until a
 * specified goal is met or the  cuttoff is reached.
 * this algorithm uses chebyshev acceleration and odd-even (checkerboard) 
 * ordering.
 */
#include "goal.h"

class successive_overrelaxation
{
public:
  // constants

  // constructors
  /* run for at most max iterations. use radius as the spectral radius of
   * the jacobi method for the chebyshev acceleration.
   */
  successive_overrelaxation(int max, double radius);
  /* place no limit on the number of iterations. */
  successive_overrelaxation(double radius);

  // methods

  // solve and return number of iters.
  int solve(problem& prob, goal& g);
  // synonym for solve
  int operator()(problem& prob, goal& g);

private:
  int cutoff;	// max iterations
  double rad;	// overrelaxation parameter
};
