/* a goal that returns true when the square of the norm of the solution is
 * less than some factor, epsilon, away from 1.
 */
#include <cmath>
#include "goal.h"

using std::abs;

class solution_norm : public goal
{
public:
  static const double DEF_EPS;	// default epsilon

  // constructors
  solution_norm(const problem& prob, double epsilon);
  solution_norm();

  // methods
  bool operator()(const problem& prob);
  static double norm(const problem& prob);

private:
  double eps;		// range

};