#include "gauss_seidel.h"

gauss_seidel::gauss_seidel(int max) : cutoff(max) {}

int gauss_seidel::solve (problem& prob, goal& g)
{
  int count = 0;
  double res;
  int I = prob.I();
  int J = prob.J();
  int i, j;

  while(!g(prob) && (count < (*this).cutoff)){
      for(i = 1; i < I; i++){
	  for(j = 1; j < J; j++){
	      res = (prob.e(i,j)*prob.at(i,j) +
		     (prob.a(i,j)*prob.at(i-1,j) + prob.b(i,j)*prob.at(i+1,j) +
		     prob.c(i,j)*prob.at(i,j-1) + prob.d(i,j)*prob.at(i,j+1)) +
		     prob.f(i,j));
	      
	      // set value
	      prob.u(i, j) = (prob.u(i, j) - res/prob.e(i,j));
	  }
      }
      ++count;
  }
  return count;
}

int gauss_seidel::operator()(problem& prob, goal& g)
{ return solve(prob, g); }
