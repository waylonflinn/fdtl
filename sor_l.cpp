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
  ostream& out = inter.output();

  out << "# initial norm:\t" << norm0 << endl;
  out << "# final norm:\t" << norm1 << endl;
  out << "# ratio:\t" << ratio << endl;
  out << "# iterations:\t" << iter << endl;

  out.precision(PRECISION);
  out << lp << endl;

}
