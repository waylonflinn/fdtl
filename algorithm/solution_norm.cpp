#include "solution_norm.h"

const double solution_norm::DEF_EPS = 1.0e-6;

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
  double line;	// integral along a grid line
  double norm;	// norm of solution, squared
  int I = prob.I();
  int J = prob.J();
  double sx, sy;
  int i, j;

  sx = prob.dx();
  sy = prob.dy();
  norm = 0;
  // calc first line
  line = 0.5*pow(prob.at(0,0),2);
  for(j = 1; j < J; ++j)
    line += pow(prob.at(0,j),2);
  line += 0.5*pow(prob.at(0,J),2);
  line *= sy;
  norm += 0.5*line;

  for(i = 1; i <= I; ++i){
    line = 0.5*pow(prob.at(i,0),2);
    for(j = 1; j < J; ++j){
      line += pow(prob.at(i,j),2);
    }
    line += 0.5*pow(prob.at(i,J),2);
    line *= sy;
    norm += line;
  }

  // calc last line
  line = 0.5*pow(prob.at(I,0),2);
  for(j = 1; j < J; ++j)
    line += pow(prob.at(I,j),2);
  line += 0.5*pow(prob.at(I,J),2);
  line *= sy;
  norm += 0.5*line;

  norm *= sx;

  return norm;
}
