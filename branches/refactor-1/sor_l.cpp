#include <iostream>
#include <vector>
#include "laplace.h"
#include "gauss_seidel.h"
#include "residual_norm.h"

#define PRECISION	3	// decimal digits to display
#define EPS		1.0e-5	// ratio of final residual to initial residual

using std::vector;
using std::cout;
using std::endl;

main(int argc, char* argv[])
{
  double b_arr[] =
    {-9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vector<double> b(b_arr, b_arr + 20);
  boundary bound(boundary::DIRICHLET, b.begin(), b.end());
  vector<double> nb(20, 0);
  boundary nbound(boundary::NEUMANN, nb.begin(), nb.end());

  laplace lp(20, 20, 20, 20, bound, bound, nbound, nbound);
  residual_norm norm(lp, EPS);
  gauss_seidel gs(10000);

  int I = lp.I();
  int J = lp.J();
  int i,j;
  double norm0, norm1, ratio;	// initial norm, final norm, ratio
  int iter;

  norm0 = residual_norm::norm(lp);
  iter = gs.solve(lp, norm);
  norm1 = residual_norm::norm(lp);
  ratio = norm1/norm0;

  cout << "# initial norm:\t" << norm0 << endl;
  cout << "# final norm:\t" << norm1 << endl;
  cout << "# ratio:\t" << ratio << endl;
  cout << "# iterations:\t" << iter << endl;

  cout.precision(PRECISION);
  for(j = J; j >= 0; --j){
    for(i = 0; i <= I; ++i){
      cout << lp.at(i, j) << " ";
    }
    cout << endl;
  }


  /// initialize

  /*

  /// process
  
  double norm_0;
  double norm;
  int iter;

  norm_0 = gs_norm(p_solution);
  iter = gs(EPS, p_solution);
  norm = gs_norm(p_solution);

  output << "# initial norm:\t" << norm_0 << endl;
  output << "# finial norm:\t" << norm << endl;
  output << "# ratio:\t" << norm/norm_0 << endl;
  output << "# iterations:\t" << iter << endl;
  */

}
