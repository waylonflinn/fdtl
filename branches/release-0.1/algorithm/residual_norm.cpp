#include "residual_norm.h"

residual_norm::residual_norm(const problem& prob, double epsilon) :
  init(residual_norm::norm(prob)), target(init*epsilon), max(100*init)
{
}

residual_norm::residual_norm() : init(1), target(1), max(1)
{
}

bool residual_norm::operator()(const problem& prob)
{
  double norm = residual_norm::norm(prob);

  return (target == 0) ||  (norm > max) || (norm < target);
}

double residual_norm::norm(const problem& prob)
{
  double res;	// residual
  double norm;	// norm of the residual
  int I = prob.I();
  int J = prob.J();
  int i, j;

  norm = 0;
  for(i = 1; i < I; ++i){
    for(j = 1; j < J; ++j){
      res = (prob.e(i,j)*prob.at(i,j) +
	     (prob.a(i,j)*prob.at(i-1,j) + prob.b(i,j)*prob.at(i+1,j) +
	      prob.c(i,j)*prob.at(i,j-1) + prob.d(i,j)*prob.at(i,j+1)) +
	     prob.f(i,j));
	    
      norm += abs(res);
    }
  }
  
  return norm;
}
