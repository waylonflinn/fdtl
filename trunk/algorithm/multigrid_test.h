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
  int m_cyc = 4;
  int iter = 0;
  int this_iter = 0;

  if(prob.I() == mg){
    iter = smooth(prob, g);
    cout << "# iter: " << iter << endl;
    cout << "# size: " << prob.I() << endl;
    cout << prob;
    (*this).init = true;
  }
  else{
    ProblemResizable orig = prob.clone();
    ProblemResizable diff = prob.clone();
    diff.left() = boundary(boundary::DIRICHLET, diff.J(), 0.0);
    ProblemResizable shrunk;
    if(init)
	this_iter += smooth(prob, g);	// presmoothing
    while((cyc < m_cyc) && !g(prob)){
      if(init){
	prob.shrink(hw);
	shrunk = prob.clone();
	iter += (*this).solve(prob, g);	// recurse
	/*cout << "# shrunk" << endl;
	  cout << shrunk;*/
	shrunk -= prob;
	shrunk.left() = boundary(boundary::DIRICHLET, shrunk.J(), 0.0);
	/*cout << "# shrunk" << endl;
	  cout << shrunk;*/
	bi(shrunk, diff);
	/*cout << "# orig" << endl;
	  cout << orig;
	cout << "# diff" << endl;
	cout << diff;*/
	orig -= diff;
	/*cout << "# orig" << endl;
	  cout << orig;*/
	this_iter += smooth(orig, g);		// postsmoothing
	prob = orig;
      }
      else{
	prob.shrink(hw);
	iter += (*this).solve(prob, g);	// recurse
	bi(prob, orig);
	this_iter += smooth(orig, g);		// postsmoothing
	prob = orig;
      }
      ++cyc;
    }
    
    cout << "# iter: " << this_iter << endl;
    cout << "# size: " << prob.I() << endl;
    cout << prob;
  }
  return iter + this_iter;
}

template<class ProblemResizable> int multigrid::operator()
  (ProblemResizable& prob, goal& g)
{ return solve(prob, g); }
