#include "solution_norm.h"

const double solution_norm::DEF_EPS = 1.0e-4;

solution_norm::solution_norm(const problem& prob, double epsilon) 
  : eps(epsilon)
{
}

solution_norm::solution_norm() : eps(solution_norm::DEF_EPS)
{
}

bool solution_norm::operator()(const problem& prob)
{
  double norm = solution_norm::norm(prob);

  return abs(1-norm) < eps;
}

double solution_norm::norm(const problem& prob)
{

  square<gross_pitaevskii> trans_square(gpe);
  integrator_open_basic integrator;

  return integrator(trans_square);
}
