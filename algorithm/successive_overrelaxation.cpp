#include <limits>
#include "successive_overrelaxation.h"

successive_overrelaxation::successive_overrelaxation(int max, double radius) 
  : cutoff(max), rad(radius) {}

successive_overrelaxation::successive_overrelaxation(double radius)
  : cutoff(std::numeric_limits<int>::max()), rad(radius) {}

int successive_overrelaxation::solve (problem& prob, goal& g)
{
  int count = 0;
  double param = 1;	// relaxation parameter
  double res;		// residual
  int I = prob.I();
  int J = prob.J();
  int i, j;
  int oe = 0;		// odd/even marker
  int is = 1, js =1;	// i and j starting indeces

  while(!g(prob) && (count < (*this).cutoff)){
    for(oe = 0; oe < 2; ++oe){
      for(i = is; i < I; i++){
	  for(j = js; j < J; j+=2){
	      res = (prob.e(i,j)*prob.at(i,j) +
		     (prob.a(i,j)*prob.at(i-1,j) + prob.b(i,j)*prob.at(i+1,j) +
		     prob.c(i,j)*prob.at(i,j-1) + prob.d(i,j)*prob.at(i,j+1)) +
		     prob.f(i,j));
	      
	      // set value
	      prob.u(i, j) = (prob.u(i, j) - res/prob.e(i,j));
	  }
	  js=3-js;	// 1 or 2
      }
      is=3-is;		// 1 or 2
    }
    ++count;
  }
  return count;
}

int successive_overrelaxation::operator()(problem& prob, goal& g)
{ return solve(prob, g); }
