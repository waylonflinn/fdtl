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
  int is = 1, os = 1;	// inner and outer starting point trackers

  while(!g(prob) && (count < (*this).cutoff)){
    for(oe = 0; oe < 2; ++oe){	// odd and even passes
      for(i = 1; i < I; i++){
	is = os;
	for(j = is; j < J; j+=2){
	  res = (prob.e(i,j)*prob.at(i,j) +
		 (prob.a(i,j)*prob.at(i-1,j) + prob.b(i,j)*prob.at(i+1,j) +
		  prob.c(i,j)*prob.at(i,j-1) + prob.d(i,j)*prob.at(i,j+1)) +
		 prob.f(i,j));
	  
	  // set value
	  prob.u(i, j) -= param*res/prob.e(i,j);
	}
	is=3-is;	// 1 or 2
      }
      os=3-os;		// 1 or 2
      param = (count == 1 && oe == 0 ? 
	       1.0/(1.0 - 0.5*rad*rad) :
	       1.0/(1.0 - 0.25*rad*rad*param));
    }
    ++count;
  }
  return count;
}

int successive_overrelaxation::operator()(problem& prob, goal& g)
{ return solve(prob, g); }
