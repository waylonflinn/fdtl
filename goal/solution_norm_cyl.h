/* a goal that returns true when the square of the norm of the solution is
 * less than some factor, epsilon, away from 1.
 * the norm calculated is the integral of the square of the solution over the
 * problem's defined domain in cylindrical coordinates.
 * The formula used for the integration (quadrature) is gotten by 
 * extending the trapezoidal rule (a quadrature formula involving two points)
 * to an arbitrary number of points, then modifing it to be open (neglect of
 * endpoints) rather  than closed (inclusion of endpoints). The result is then
 * generalized to two dimensions.
 * This formula is a multidimensional form of equation (4.1.16) from
 * 'Numerical Recipes in C'. A reasonably good derivation of the single
 * dimensional form is given there.
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
