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
  // double in size
  virtual void grow(operator_prolong& op) const = 0;
  // half
  virtual void shrink(operator_restrict& op) const = 0;
};

#endif	// PDE_PROBLEM_RESIZABLE
