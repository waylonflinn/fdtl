/* an abstract class representing a solver for a finite differenced pde.
 */
#include "goal.h"

class solver
{
public:
  // methods

  // solve and return number of iters.
  virtual int solve(problem& prob, goal& g) = 0;
  // synonym for solve
  virtual int operator()(problem& prob, goal& g) = 0;
};
