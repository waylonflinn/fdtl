/* a goal that returns true when the norm of the residual is less than 
 * the initial norm times some factor, epsilon (which is generally between
 * zero and one).
 */
#include <cmath>
#include "goal.h"

using std::abs;

class residual_norm : public goal
{
public:
  // constructors
  residual_norm(const problem& prob, double epsilon);
  residual_norm();

  // methods
  bool operator()(const problem& prob);
  static double norm(const problem& prob);

private:
  double target;	// initial norm times epsilon
  
};
