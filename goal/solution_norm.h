/* a goal that returns true when the square of the norm of the solution is
 * less than some factor, epsilon, away from 1.
 * the norm calculated is the integral of the sqaure of the solution over the
 * problem's defined domain.
 */
#ifndef PDE_SOLUTION_NORM
#define PDE_SOLUTION_NORM

#include <cmath>
#include "goal.h"
#include "square.h"
#include "integrator_open_basic.h"

using std::abs;

template <class StaticSolution>
class solution_norm
{
public:
  static const double DEF_EPS;	// default epsilon

  // constructors
  solution_norm(const StaticSolution& solution, double epsilon);
  solution_norm();

  // methods
  bool operator()(const StaticSolution& solution);
  static double norm(const StaticSolution& solution);

private:
  double eps;		// range

};

template <class StaticSolution>
const double solution_norm<StaticSolution>::DEF_EPS = 1.0e-4;

template <class StaticSolution>
solution_norm<StaticSolution>::solution_norm(const StaticSolution& solution, double epsilon) 
  : eps(epsilon)
{
}

template <class StaticSolution>
solution_norm<StaticSolution>::solution_norm() : eps(solution_norm::DEF_EPS)
{
}

template <class StaticSolution>
bool solution_norm<StaticSolution>::operator()(const StaticSolution& solution)
{
  double norm = solution_norm<StaticSolution>::norm(solution);

  return abs(1-norm) < eps;
}

template <class StaticSolution>
double solution_norm<StaticSolution>::norm(const StaticSolution& solution)
{

  square<StaticSolution> trans_square(solution);
  integrator_open_basic integrator;

  return integrator(trans_square);
}

#endif	// PDE_SOLUTION_NORM
