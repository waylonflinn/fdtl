#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>
#include "laplace.h"
#include "gauss_seidel.h"
#include "residual_norm.h"
#include "bilinear_interpolation.h"
#include "half_weighting.h"

#define EPS 1.0e-5

using std::cout;
using std::endl;
using std::vector;
using std::pair;

gauss_seidel smooth(5000);
bool init = false;
template<class ProblemResizable> int solve(ProblemResizable& prob, goal& g);
int multi(laplace& lp);
int main()
{
  int I,J;
  I = J = 40;
  pair<double, double> x(-4,4);
  pair<double, double> y(-4,4);
  double arr_bound[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
  vector<double> vec_bound(arr_bound, arr_bound + 20);
  vec_bound.insert(vec_bound.end(),vec_bound.rbegin(),vec_bound.rend());

  boundary bound_f(boundary::DIRICHLET, J, 0.0);
  //boundary bound_f_odd(boundary::DIRICHLET, vec_bound.begin(), vec_bound.end());
  boundary bound_f_odd(boundary::DIRICHLET, J, 1.0);
  laplace fine(I, J, x, y, bound_f, bound_f, bound_f, bound_f_odd);
  residual_norm norm(fine, EPS);

  double norm_c0 = residual_norm::norm(fine);
  int iter = solve(fine, norm);

  double norm_c1 = residual_norm::norm(fine);
  double ratio = norm_c1/norm_c0;

  cout.precision(3);

  cout << "# iter: " << iter << endl;
  cout << "# ratio: " << ratio << endl;

  cout << fine << endl;

  return 0;
}

// recursive templated version
template<class ProblemResizable> int solve(ProblemResizable& prob, goal& g)
{

  bilinear_interpolation bi;
  half_weighting hw;
  int iter = 0;
  int this_iter = 0;
  int cycle = 0;
  int max_cycle = 3;
  int min_grid = 5;

  if(prob.I() == min_grid){
    iter = smooth(prob, g);
    cout << "# iter: " << iter << endl;
    cout << "# size: " << prob.I() << endl;
    cout << prob;
  }
  else{
    ProblemResizable orig = prob.clone();
    prob.shrink(hw);
    iter = solve(prob, g);		// recurse
    bi(prob, orig);
    this_iter += smooth(orig, g);	// postsmoothing
    prob = orig;
    iter += this_iter;
    cout << "# iter: " << this_iter << endl;
    cout << "# size: " << prob.I() << endl;
    cout << prob;
  }
  return iter;
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

  int size = I;
  laplace size_set[depth+1];
  residual_norm norm(lp, EPS);
  bilinear_interpolation bi;
  half_weighting hw;
  gauss_seidel gs(20000);


  // generate set of problems
  int count = 0;
  size_set[count++]=lp.clone();
  while(size != min_size){
    size = size/2;
    lp.shrink(hw);
    size_set[count++]=lp.clone();
  }

  iter = gs.solve(size_set[depth], norm);

  cout << "# iter " << min_size << ": " << iter << endl;
  cout << lp << endl;

  size *= 2;
  int iter_i =0;
  while(size <= I){
    bi(size_set[depth], size_set[depth-1]);
    iter_i =gs.solve(size_set[--depth], norm); 
    iter += iter_i;
    cout << "# iter " << size << ": " << iter_i << endl;
    cout << size_set[depth] << endl;
    size *= 2;
  }

  lp = size_set[0];
  return iter;
}
