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
  boundary bound_f_odd(boundary::DIRICHLET, vec_bound.begin(), vec_bound.end());
  laplace fine(I, J, x, y, bound_f, bound_f, bound_f, bound_f_odd);
  /*
  double norm_c0 = residual_norm::norm(fine);
  int iter = multi(fine);

  double norm_c1 = residual_norm::norm(fine);
  double ratio = norm_c1/norm_c0;
  */
  
  boundary bound_c(boundary::DIRICHLET, J/2, 0.0);
  boundary bound_c_odd(boundary::DIRICHLET, J/2, 1.0);
  half_weighting hw;
  hw(bound_f_odd,bound_c_odd);
  laplace coarse(I/2, J/2, x, y, bound_c, bound_c, bound_c, bound_c_odd);

  hw(fine, coarse);
  
  bilinear_interpolation bi;
  bi(bound_c_odd, bound_f_odd);
  fine = laplace(I, J, x, y, bound_f, bound_f, bound_f, bound_f_odd);
  
  cout.precision(3);

  //cout << "# iter: " << iter << endl;
  //cout << "# ratio: " << ratio << endl;

  //cout << coarse << endl;

  cout << fine << endl;

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

  int size = mult;
  residual_norm norm(lp, EPS);
  bilinear_interpolation bi;
  gauss_seidel gs(20000);
  boundary top, right, bottom, left;
  top = boundary(boundary::DIRICHLET, size, 0.0);
  right = boundary(top);
  bottom= boundary(top);
  left= boundary(boundary::DIRICHLET, size, 1.0);
  bi(lp.left(),left);
  laplace base(size, size, x, y, top, right, bottom, left);


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
    bi(old_lp.left(),left);
    old_lp = new_lp;
    new_lp = laplace(size, size, x, y, top, right, bottom, left);
    bi(old_lp, new_lp);
    iter_i =gs.solve(new_lp, norm); 
    iter += iter_i;
    cout << "# iter " << size << ": " << iter_i << endl;
    size *= 2;
  }
  if(min_size < I){
    bi(new_lp, lp);
    iter_i= gs.solve(lp, norm);
    cout << "# iter " << size << ": " << iter_i << endl;
    iter += iter_i;
  }
  else
    lp = base;

  return iter;
}
