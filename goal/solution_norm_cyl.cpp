#include "solution_norm_cyl.h"


const double solution_norm_cyl::DEF_EPS = 1.0e-4;

solution_norm_cyl::solution_norm_cyl(const problem& prob, double epsilon) 
  : eps(epsilon)
{
}

solution_norm_cyl::solution_norm_cyl() : eps(solution_norm_cyl::DEF_EPS)
{
}

bool solution_norm_cyl::operator()(const problem& prob)
{
  double norm = solution_norm_cyl::norm(prob);

  return abs(1-norm) < eps;
}

double solution_norm_cyl::norm(const problem& prob)
{
  square<gross_pitaevskii> trans_square(gpe);
  jacobian_cyl<square<gross_pitaevskii> > trans_cyl(trans_square);
  integrator_open_basic integrator;
  
  return integrator(trans_cyl);
}
