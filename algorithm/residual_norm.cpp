#include "residual_norm.h"

residual_norm::residual_norm(const problem& prob, double epsilon)
{
  (*this).target = (epsilon * residual_norm::norm(prob));
}

residual_norm::residual_norm() : target(1)
{
}

bool residual_norm::operator()(const problem& prob)
{ return (target == 0) || (residual_norm::norm(prob) < (*this).target); }

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
