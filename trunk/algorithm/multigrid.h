/* a very simple linear multigrid system which uses nested iteration with
 * bilinear interpolation for the prolongation operator and the standard
 * half weighting operator for restriction.
 * applies the smoother to the problem, beggining on the smallest grid, until
 * the goal is reached then prolongs the solution to next finer grid until
 * the desired grid size is reached.
 * boundary conditions for each grid are generated from those of the problem
 * using the restriction operator.
 */
#include "gauss_seidel.h"
#include "bilinear_interpolation.h"
#include "half_weighting.h"
#include <utility>

using std::pair;

class multigrid
{
public:
  // constants

  const static int DEF_BASE = 5;

  // constructors
  /* run for at most 'iter' iterations, starting on a square grid with 'base'
   * points to a side, using 'smoother' to smooth at each step.
   */
  multigrid(int iter, int base, solver& smoother);
  multigrid();	// any number of iterations, using gauss-seidel to smooth

  // methods

  // solve and return number of iters.
  template<class ProblemResizable> int solve(ProblemResizable& prob, goal& g);
  // synonym for solve
  template<class ProblemResizable> int operator()
    (ProblemResizable& prob, goal& g);

private:
  bool init;
  int co;
  int mg;		// size of the smallest grid
  gauss_seidel def_smooth;
  solver& smooth;	// smoother

};

/* recursive templated version
 * requires operator+=(), operator-=(), shrink(), and clone()
 */
template<class ProblemResizable> int multigrid::solve(ProblemResizable& prob, goal& g)
{
  bilinear_interpolation bi;
  half_weighting hw;
  int cyc = 0;
  int m_cyc = 2;
  int iter = 0;

  if(prob.I() == mg){
    iter = smooth(prob, g);
    (*this).init = true;
  }
  else{
    ProblemResizable orig = prob.clone();
    ProblemResizable diff = prob.clone();
    ProblemResizable shrunk;
    while((cyc < m_cyc) && !g(prob)){
      if(init){
	iter += smooth(orig, g);	// presmooting
	prob.shrink(hw);
	shrunk = prob.clone();
	iter += (*this).solve(prob, g);	// recurse
	shrunk -= prob;
	bi(shrunk, diff);
	orig -= diff;
	iter += smooth(orig, g);		// postsmoothing
	prob = orig;
      }
      else{
	prob.shrink(hw);
	iter += (*this).solve(prob, g);	// recurse
	bi(prob, orig);
	iter += smooth(orig, g);		// postsmoothing
	prob = orig;
      }
      ++cyc;
    }
  }
  return iter;
}

template<class ProblemResizable> int multigrid::operator()
  (ProblemResizable& prob, goal& g)
{ return solve(prob, g); }
