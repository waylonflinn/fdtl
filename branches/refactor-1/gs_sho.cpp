#include <iostream>
#include <vector>
#include "interface_sho.h"
#include "simple_harmonic_oscillator.h"
#include "gauss_seidel.h"
#include "residual_norm.h"
#include "solution_norm.h"

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
  solution_norm s_norm(sho, EPS);
  gauss_seidel gs(10000);

  int I = sho.I();
  int J = sho.J();
  double norm0, norm1, ratio;	// initial norm, final norm, ratio
  double s_norm0;
  int iter;
  ostream& out = inter.output();

  norm0 = residual_norm::norm(sho);
  iter = gs.solve(sho, norm);
  norm1 = residual_norm::norm(sho);
  ratio = norm1/norm0;
  s_norm0 = solution_norm::norm(sho);

  out << "# initial norm:\t" << norm0 << endl;
  out << "# final norm:\t" << norm1 << endl;
  out << "# ratio:\t" << ratio << endl;
  out << "# iterations:\t" << iter << endl;
  out << "# sol norm:\t" << s_norm0 << endl;

  out.precision(PRECISION);
  out << sho;
}
