#include <iostream>
#include <vector>
#include <cmath>
#include "interface.h"
#include "laplace.h"
#include "successive_overrelaxation.h"
#include "residual_norm.h"

#define PRECISION	3	// decimal digits to display
#define EPS		1.0e-5	// ratio of final residual to initial residual

using std::vector;
using std::cout;
using std::endl;

main(int argc, char* argv[])
{
  interface inter;

  try{
  inter = interface("gs_l", argc, argv);
  }
  catch(invalid_argument e){
    cerr << e.what() << endl;
    return 1;
  }
  catch(...){
    cerr << "something bad happened!" << endl;
    return 1;
  }

  laplace lp(inter.I(), inter.J(), inter.x(), inter.y(),
	     inter.top(), inter.right(), inter.bottom(), inter.left());
 
  residual_norm norm(lp, EPS);
  successive_overrelaxation sor(10000, 1-M_PI*M_PI/(2*60*60));

  int I = lp.I();
  int J = lp.J();
  int i,j;
  double norm0, norm1, ratio;	// initial norm, final norm, ratio
  int iter;

  norm0 = residual_norm::norm(lp);
  iter = sor.solve(lp, norm);
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
