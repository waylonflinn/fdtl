#include "jacobian_cyl.h"

template <class StaticSolution>
jacobian_cyl<StaticSolution>::jacobian_cyl<StaticSolution>(const StaticSolution& solution)
{
  sol=solution;
}

template <class StaticSolution>
double jacobian_cyl<StaticSolution>::at(int i, int j)
{
  return sol.at(i,j)*2*M_PI*(sol.x0()+(sol.dx()*i));
}
