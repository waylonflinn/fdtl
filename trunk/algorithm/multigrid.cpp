#include <limits>
#include "multigrid.h"

multigrid::multigrid(int max, solver& smoother) : 
  solver_basic(max), smooth(smoother) {}

multigrid::multigrid() :
  solver_basic(), def_smooth(100), smooth(def_smooth) {}

int multigrid::solve (problem_resizable& prob, goal& g)
{
  int min_size = 5;
  int iter = 0;
  double res;		// residual
  int I = prob.I();
  int J = prob.J();
  int i, j;
  int mult;
  int depth;
  pair<double, double> x(-4,4);
  pair<double, double> y(-4,4);
  
  if(I != J)
    return 0;

  if(I < min_size)
    return 0;

  // find depth of recursion
  mult = I;
  depth = 0;
  while(mult != min_size && mult != 0){
    mult >>= 1;
    depth++;
  }
  if(mult == 0)
    return 0;

  int size = mult;
  boundary top, right, bottom, left;
  top = boundary(boundary::DIRICHLET, size, 0.0);
  right = boundary(top);
  bottom= boundary(top);
  left= boundary(boundary::DIRICHLET, size, 1.0);
  Problem base(size, size, x, y, top, right, bottom, left);

  iter = smooth.solve(base, goal);
  cout << "# iter " << min_size << ": " << iter << endl;
  prob old_prob(base), new_prob(base);
  size *= 2;
  int iter_i =0;
  while(size < I){
    top = boundary(boundary::DIRICHLET, size, 0.0);
    right = boundary(top);
    bottom= boundary(top);
    left = boundary(boundary::DIRICHLET, size, 1.0);
    old_prob = new_prob;
    new_prob = laplace(size, size, x, y, top, right, bottom, left);
    prolong(old_prob, new_prob);
    iter_i =smooth.solve(new_prob, norm); 
    iter += iter_i;
    cout << "# iter " << size << ": " << iter_i << endl;
    size *= 2;
  }
  if(min_size < I){
    bilinear_interp(new_prob, prob);
    iter_i= smooth.solve(prob, norm);
    cout << "# iter " << size << ": " << iter_i << endl;
    iter += iter_i;
  }
  else
    prob = base;

  return iter;
}

int multigrid::operator()(problem_resizable& prob, goal& g)
{ return solve(prob, g); }

void restrict(vector<vector<double> >& fine,
		 vector<vector<double> >& coarse)
{

  int fI,fJ;
  int cI,cJ;
  cI = coarse.size();
  fI = fine.size();
  if(fI == 0 || cI == 0)
    return;
  else{
    cJ = coarse[0].size();
    fJ = fine[0].size();
  }
  int ci, cj;
  int fi, fj;

  vector<vector<double> >::iterator it_coarse(coarse.begin());
  vector<vector<double> >::iterator it_fine(fine.begin());
  for(fi=2,ci=1;ci < cI-1; ++ci, fi+=2){
    for(fj=2,cj=1; cj < cJ-1; ++cj, fj+=2){
      it_coarse[ci][cj] = 0.5*it_fine[fi][fj]+
	0.125*(it_fine[fi-1][fj] + it_fine[fi+1][fj] +
	      it_fine[fi][fj-1] + it_fine[fi][fj+1]);
    }
  }
}
