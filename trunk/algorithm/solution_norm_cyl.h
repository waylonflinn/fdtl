/* a goal that returns true when the square of the norm of the solution is
 * less than some factor, epsilon, away from 1.
 * the norm calculated is the integral of the sqaure of the solution over the
 * problem's defined domain in cylindrical coordinates.
 * a multidimensional form of equation (4.1.16) from 'Numerical Recipes in C'
 * is used for the integration (quadrature).
 */
#include <cmath>
#include "goal.h"

using std::abs;

class solution_norm_cyl : public goal
{
public:
  static const double DEF_EPS;	// default epsilon

  // constructors
  solution_norm_cyl(const problem& prob, double epsilon);
  solution_norm_cyl();

  // methods
  bool operator()(const problem& prob);
  static double norm(const problem& prob);

private:
  double eps;		// range

};
