/* abstract goal class. tests whether or not a problem has a solution in a
 * goal state.
 */

#ifndef PDE_GOAL
#define PDE_GOAL

#include "problem.h"

class goal
{
public:
  virtual bool operator()(const problem& prob) = 0;
};

#endif	// PDE_GOAL
