#include "integrator_open_basic.h"

integrator_open_basic::integrator_open_basic()
{
}

template<class StaticSolution>
double integrator_open_basic::operator()(const StaticSolution& solution)
{
  double line;	// integral along a grid line
  double result;	// result of integral
  int I = solution.I();
  int J = solution.J();
  double sx, sy;
  int i, j;

  sx = solution.dx();
  sy = solution.dy();
  result = 0;

  // calc first (interior) line
  line = (23.0/12.0)*solution.at(1,1);
  line += (7.0/12.0)*solution.at(1,2);
  for(j = 3; j < J-2; ++j)
    line += solution.at(1,j);
  line += (7.0/12.0)*solution.at(1,J-2);
  line += (23.0/12.0)*solution.at(1,J-1);
  line *= sy;
  result += (23.0/12.0)*line;

  // second
  line = (23.0/12.0)*solution.at(2,1);
  line += (7.0/12.0)*solution.at(2,2);
  for(j = 3; j < J-2; ++j)
    line += solution.at(2,j);
  line += (7.0/12.0)*solution.at(2,J-2);
  line += (23.0/12.0)*solution.at(2,J-1);
  line *= sy;
  result += (7.0/12.0)*line;

  // interior values
  for(i = 3; i < I-2; ++i){
    line = (23.0/12.0)*solution.at(i,1);
    line += (7.0/12.0)*solution.at(i,2);
    for(j = 3; j < J-2; ++j){
      line += solution.at(i,j);
    }
    line += (7.0/12.0)*solution.at(i,J-2);
    line += (23.0/12.0)*solution.at(i,J-1);
    line *= sy;
    result += line;
  }

  // next to last
  line = (23.0/12.0)*solution.at(I-2,1);
  line += (7.0/12.0)*solution.at(I-2,2);
  for(j = 3; j < J-2; ++j)
    line += solution.at(I-2,j);
  line += (7.0/12.0)*solution.at(I-2,J-2);
  line += (23.0/12.0)*solution.at(I-2,J-1);
  line *= sy;
  result += (7.0/12.0)*line;

  // last
  line = (23.0/12.0)*solution.at(I-1,1);
  line += (7.0/12.0)*solution.at(I-1,2);
  for(j = 3; j < J-2; ++j)
    line += solution.at(I-1,j);
  line += (7.0/12.0)*solution.at(I-1,J-2);
  line += (23.0/12.0)*solution.at(I-1,J-1);
  line *= sy;
  result += (23.0/12.0)*line;

  result *= sx;

  return result;

}
