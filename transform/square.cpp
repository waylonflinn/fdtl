#include "square.h"

template <class StaticSolution>
square<StaticSolution>::square<StaticSolution>(const StaticSolution& solution)
{
  sol=solution;
}

template <class StaticSolution>
double square<StaticSolution>::at(int i, int j)
{
  return sol.at(i,j)*sol.at(i,j);
}
