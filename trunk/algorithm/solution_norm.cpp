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
  double area;	// area of an element
  double norm;	// norm of solution, squared
  int I = prob.I();
  int J = prob.J();
  double sxsy = prob.dx()*prob.dy();
  int i, j;

  norm = 0;
  for(i = 1; i <= I; ++i){
    for(j = 1; j <= J; ++j){
      area =
	sxsy*(pow(prob.at(i-1,j-1),2)+
	      pow(prob.at(i,j-1),2)+
	      pow(prob.at(i-1,j),2)+
	      pow(prob.at(i,j),2))/4;

      norm += area;
    }
  }

  return norm;
}
