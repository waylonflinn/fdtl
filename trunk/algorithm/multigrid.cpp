#include <limits>
#include "multigrid.h"

multigrid::multigrid(int max, solver& smoother) : 
  cutoff(max), smooth(smoother) {}

multigrid::multigrid() :
  cutoff(std::numeric_limits<int>::max()), def_smooth(100),
  smooth(def_smooth) {}

template<class Problem> int multigrid::solve (Problem& prob, goal& g)
{
  int count = 0;
  double res;		// residual
  int I = prob.I();
  int J = prob.J();
  int i, j;
  int mult;
  int depth;
  Problem base(prob);

  if(I != J)
    return 0;

  // find depth of recursion
  mult = I;
  depth = 0;
  while(mult != 5 && mult != 0){
    mult >>= 1;
    depth++;
  }
  if(mult = 0)
    return 0;
  
  while(--depth != 0)
  
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

template<class Problem> int multigrid::operator()(Problem& prob, goal& g)
{ return solve(prob, g); }
