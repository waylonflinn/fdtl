/* a goal that returns true when the square of the norm of the solution is
 * less than some factor, epsilon, away from 1.
 * the norm calculated is the integral of the square of the solution over the
 * problem's defined domain in cylindrical coordinates.
 */
#ifndef PDE_SOLUTION_NORM_CYL
#define PDE_SOLUTION_NORM_CYL

#include <cmath>
#include "goal.h"
#include "square.h"
#include "jacobian_cyl.h"
#include "integrator_open_basic.h"

using std::abs;

template <class StaticSolution>
class solution_norm_cyl
{
public:
  static const double DEF_EPS;	// default epsilon

  // constructors
  solution_norm_cyl(const StaticSolution& solution, double epsilon);
  solution_norm_cyl();

  // methods
  bool operator()(const StaticSolution& solution);
  static double norm(const StaticSolution& solution);

private:
  double eps;		// range

};

template <class StaticSolution>
const double solution_norm_cyl<StaticSolution>::DEF_EPS = 1.0e-4;

template <class StaticSolution>
solution_norm_cyl<StaticSolution>::solution_norm_cyl(const StaticSolution& solution, double epsilon) 
  : eps(epsilon)
{
}

template <class StaticSolution>
solution_norm_cyl<StaticSolution>::solution_norm_cyl() : eps(solution_norm_cyl::DEF_EPS)
{
}

template <class StaticSolution>
bool solution_norm_cyl<StaticSolution>::operator()(const StaticSolution& solution)
{
  double norm = solution_norm_cyl::norm(solution);

  return abs(1-norm) < eps;
}

template <class StaticSolution>
double solution_norm_cyl<StaticSolution>::norm(const StaticSolution& solution)
{
  square<StaticSolution> trans_square(solution);
  jacobian_cyl<square<StaticSolution> > trans_cyl(trans_square);
  integrator_open_basic integrator;
  
  return integrator(trans_cyl);
}

#endif	// PDE_SOLUTION_NORM_CYL
