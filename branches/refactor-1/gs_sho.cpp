#include <iostream>
#include <vector>
#include "interface_sho.h"
#include "simple_harmonic_oscillator.h"
#include "gauss_seidel.h"
#include "residual_norm.h"

#define PRECISION	3	// decimal digits to display
#define EPS		1.0e-5	// ratio of final residual to initial residual

using std::vector;
using std::cout;
using std::endl;

main(int argc, char* argv[])
{
  interface_sho inter;

  try{
  inter = interface_sho("gs_sho", argc, argv);
  }
  catch(invalid_argument e){
    cerr << e.what() << endl;
    return 1;
  }
  catch(...){
    cerr << "something bad happened!" << endl;
    return 1;
  }

  simple_harmonic_oscillator sho(inter.I(), inter.J(), inter.x(), inter.y(),
	     inter.top(), inter.right(), inter.bottom(), inter.left(),
	     inter.a(), inter.b(), inter.eigenvalue());
  residual_norm norm(sho, EPS);
  gauss_seidel gs(10000);

  int I = sho.I();
  int J = sho.J();
  int i,j;
  double norm0, norm1, ratio;	// initial norm, final norm, ratio
  int iter;

  norm0 = residual_norm::norm(sho);
  iter = gs.solve(sho, norm);
  norm1 = residual_norm::norm(sho);
  ratio = norm1/norm0;

  cout << "# initial norm:\t" << norm0 << endl;
  cout << "# final norm:\t" << norm1 << endl;
  cout << "# ratio:\t" << ratio << endl;
  cout << "# iterations:\t" << iter << endl;
  //  cout << "# func norm:\t" << func_norm << endl;

  cout.precision(PRECISION);
  for(j = J; j >= 0; --j){
    for(i = 0; i <= I; ++i){
      cout << sho.at(i, j) << " ";
    }
    cout << endl;
  }

}
