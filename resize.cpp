#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include "next.cpp"
#include "laplace.h"
#include "gauss_seidel.h"
#include "residual_norm.h"

#define EPS 1.0e-5

using std::cout;
using std::endl;
using std::vector;
using std::pair;

next n(1);
double filler();
int multi(laplace& lp);
void bilinear_interp(problem& coarse,
		  problem& fine);
void half_weight(problem& fine,
		 problem& coarse);
void print(const vector<vector<double> >& V);
int main()
{
  int I,J;
  I = J = 80;
  pair<double, double> x(-4,4);
  pair<double, double> y(-4,4);

  boundary bound_f(boundary::DIRICHLET, J, 0.0);
  boundary bound_f_odd(boundary::DIRICHLET, J, 1.0);
  laplace fine(I, J, x, y, bound_f, bound_f, bound_f, bound_f_odd);
  
  double norm_c0 = residual_norm::norm(fine);
  int iter = multi(fine);

  double norm_c1 = residual_norm::norm(fine);
  double ratio = norm_c1/norm_c0;

  cout.precision(3);

  cout << "# iter: " << iter << endl;
  cout << "# ratio: " << ratio << endl;

  //cout << coarse << endl;

  cout << fine << endl;

  /*
  bilinear_interp(V,fine);

  half_weight(fine,coarse);
  */
  return 0;
}

int multi(laplace& lp)
{
  int min_size = 5;
  int iter = 0;
  double res;		// residual
  int I = lp.I();
  int J = lp.J();
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

  residual_norm norm(lp, EPS);
  int size = mult;
  boundary top, right, bottom, left;
  top = boundary(boundary::DIRICHLET, size, 0.0);
  right = boundary(top);
  bottom= boundary(top);
  left= boundary(boundary::DIRICHLET, size, 1.0);
  laplace base(size, size, x, y, top, right, bottom, left);
  gauss_seidel gs(20000);

  iter = gs.solve(base, norm);
  cout << "# iter " << min_size << ": " << iter << endl;
  laplace old_lp(base), new_lp(base);
  size *= 2;
  int iter_i =0;
  while(size < I){
    top = boundary(boundary::DIRICHLET, size, 0.0);
    right = boundary(top);
    bottom= boundary(top);
    left = boundary(boundary::DIRICHLET, size, 1.0);
    old_lp = new_lp;
    new_lp = laplace(size, size, x, y, top, right, bottom, left);
    bilinear_interp(old_lp, new_lp);
    iter_i =gs.solve(new_lp, norm); 
    iter += iter_i;
    cout << "# iter " << size << ": " << iter_i << endl;
    size *= 2;
  }
  if(min_size < I){
    bilinear_interp(new_lp, lp);
    iter_i= gs.solve(lp, norm);
    cout << "# iter " << size << ": " << iter_i << endl;
    iter += iter_i;
  }
  else
    lp = base;

  return iter;
}

double filler()
{
  return 2*n();
}

/* if N+1 is the coarse dimension, fine must be 2N+1
 * uses random access iterator requirement (subscripting)
 */
void bilinear_interp(problem& coarse, problem& fine)
{
  int fI,fJ;
  int cI,cJ;
  int ci, cj;
  int fi, fj;
  cI = coarse.I();
  fI = fine.I();
  cJ = coarse.J();
  fJ = fine.I();

 // existing points: odd rows, odd columns
  for(fi=2,ci=1;ci < cI; ++ci, fi+=2){
    for(fj=2,cj=1; cj < cJ; ++cj, fj+=2){
      fine.u(fi,fj) = coarse.at(ci,cj);
    }
  }
  /* even rows, odd columns, interpolate vertically
   */
  for(fi=1;fi < fI; fi+=2){
    for(fj=2; fj < fJ;fj+=2){
      fine.u(fi,fj) = 0.5*(fine.at(fi-1,fj)+fine.at(fi+1,fj));
    }
  }

  /* all even columns, interpolate horizontally
   */
  for(fj=1;fj < fJ; fj+=2){
    for(fi=1; fi < fI;++fi){
      fine.u(fi,fj) = 0.5*(fine.at(fi,fj-1)+fine.at(fi,fj+1));
    }
  }
}

void half_weight(vector<vector<double> >& fine,
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
