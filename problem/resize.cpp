#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include "next.cpp"
#include "laplace.h"
#include "gauss_seidel.h"
#include "residual_norm.h"

using std::cout;
using std::endl;
using std::vector;
using std::pair;

next n(1);
double filler();
void bilinear_interp(problem& coarse,
		  problem& fine);
void half_weight(problem& fine,
		 problem& coarse);
void print(const vector<vector<double> >& V);
int main()
{
  int I,J;
  I = J = 10;
  pair<double, double> x(-4,4);
  pair<double, double> y(-4,4);

  vector<double> interior_c(J, 0);
  boundary bound_c(boundary::DIRICHLET, interior_c.begin(), interior_c.end());
  laplace coarse(I, J, x, y, bound_c, bound_c, bound_c, bound_c);

  vector<double> interior_f(2*J, 0);
  boundary bound_f(boundary::DIRICHLET, interior_f.begin(), interior_f.end());
  laplace fine(2*I, 2*J, x, y, bound_f, bound_f, bound_f, bound_f);

  
  cout.precision(3);

  cout << coarse << endl;

  cout << fine << endl;

  /*
  bilinear_interp(V,fine);

  half_weight(fine,coarse);
  */
  return 0;
}

double filler()
{
  return 2*n();
}

/* if N+1 is the coarse dimension, fine must be 2N+1
 * uses random access iterator requirement (subscripting)
 */
void bilinear_interp(vector<vector<double> >& coarse,
		  vector<vector<double> >& fine)
{
  int fI,fJ;
  int cI,cJ;
  cI = coarse.size() - 1;
  fI = fine.size() - 1;
  if(fI == 0 || cI == 0)
    return;
  else{
    cJ = coarse[0].size() - 1;
    fJ = fine[0].size() - 1;
  }
  int ci, cj;
  int fi, fj;

  vector<vector<double> >::iterator it(coarse.begin());
  vector<vector<double> >::iterator it_fine(fine.begin());
  // existing points: odd rows, odd columns
  for(fi=2,ci=1;ci < cI; ++ci, fi+=2){
    for(fj=2,cj=1; cj < cJ; ++cj, fj+=2){
      it_fine[fi][fj] = it[ci][cj];
    }
  }
  /* even rows, odd columns, interpolate vertically
   */
  for(fi=1;fi < fI; fi+=2){
    for(fj=2; fj < fJ;fj+=2){
      it_fine[fi][fj] = 0.5*(it_fine[fi-1][fj]+it_fine[fi+1][fj]);
    }
  }
  /* all even columns, interpolate horizontally
   */

  for(fj=1;fj < fJ; fj+=2){
    for(fi=1; fi < fI;++fi){
      it_fine[fi][fj] = 0.5*(it_fine[fi][fj-1]+it_fine[fi][fj+1]);
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
