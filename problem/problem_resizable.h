/* an interface adding two additional methods to the problem interface.
 * these methods are intended to allow a problem to be resized, by either
 * doubling or halfing it's size.
 */

#ifndef PDE_PROBLEM_RESIZABLE
#define PDE_PROBLEM_RESIZABLE

#include "problem.h"
#include "operator_prolong.h"
#include "operator_restrict.h"

class problem_resizable : public problem
{
public:

  virtual problem grow(operator_prolong& op) = 0;	// double in size
  virtual problem shrink(operator_restrict& op) = 0;	// half
};

#endif	// PDE_PROBLEM_RESIZABLE
