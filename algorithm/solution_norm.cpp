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
  double line;	// integral along a grid line
  double norm;	// norm of solution, squared
  int I = prob.I();
  int J = prob.J();
  double sx, sy;
  int i, j;

  sx = prob.dx();
  sy = prob.dy();
  norm = 0;

  // calc first (interior) line
  line = (23.0/12.0)*pow(prob.at(1,1),2);
  line += (7.0/12.0)*pow(prob.at(1,2),2);
  for(j = 3; j < J-2; ++j)
    line += pow(prob.at(1,j),2);
  line += (7.0/12.0)*pow(prob.at(1,J-2),2);
  line += (23.0/12.0)*pow(prob.at(1,J-1),2);
  line *= sy;
  norm += (23.0/12.0)*line;

  // second
  line = (23.0/12.0)*pow(prob.at(2,1),2);
  line += (7.0/12.0)*pow(prob.at(2,2),2);
  for(j = 3; j < J-2; ++j)
    line += pow(prob.at(2,j),2);
  line += (7.0/12.0)*pow(prob.at(2,J-2),2);
  line += (23.0/12.0)*pow(prob.at(2,J-1),2);
  line *= sy;
  norm += (7.0/12.0)*line;

  for(i = 3; i < I-2; ++i){
    line = (23.0/12.0)*pow(prob.at(i,1),2);
    line += (7.0/12.0)*pow(prob.at(i,2),2);
    for(j = 3; j < J-2; ++j){
      line += pow(prob.at(i,j),2);
    }
    line += (7.0/12.0)*pow(prob.at(i,J-2),2);
    line += (23.0/12.0)*pow(prob.at(i,J-1),2);
    line *= sy;
    norm += line;
  }

  // next to last
  line = (23.0/12.0)*pow(prob.at(I-2,1),2);
  line += (7.0/12.0)*pow(prob.at(I-2,2),2);
  for(j = 3; j < J-2; ++j)
    line += pow(prob.at(I-2,j),2);
  line += (7.0/12.0)*pow(prob.at(I-2,J-2),2);
  line += (23.0/12.0)*pow(prob.at(I-2,J-1),2);
  line *= sy;
  norm += (7.0/12.0)*line;

  // last
  line = (23.0/12.0)*pow(prob.at(I-1,1),2);
  line += (7.0/12.0)*pow(prob.at(I-1,2),2);
  for(j = 3; j < J-2; ++j)
    line += pow(prob.at(I-1,j),2);
  line += (7.0/12.0)*pow(prob.at(I-1,J-2),2);
  line += (23.0/12.0)*pow(prob.at(I-1,J-1),2);
  line *= sy;
  norm += (23.0/12.0)*line;

  norm *= sx;

  return norm;
}
