#include <iostream>
#include <vector>
#include <cmath>
#include "interface_sor_sho.h"
#include "simple_harmonic_oscillator.h"
#include "successive_overrelaxation.h"
#include "residual_norm.h"

#define PRECISION	3	// decimal digits to display
#define EPS		1.0e-5	// ratio of final residual to initial residual

using std::vector;
using std::cout;
using std::endl;

main(int argc, char* argv[])
{
  interface_sor_sho inter;

  try{
  inter = interface_sor_sho("sor_sho", argc, argv);
  }
  catch(invalid_argument e){
    cerr << e.what() << endl;
    return 1;
  }
  catch(help_exception){ return 0; }
  catch(...){
    cerr << "something bad happened!" << endl;
    return 1;
  }

  simple_harmonic_oscillator sho(inter.I(), inter.J(), inter.x(), inter.y(),
	     inter.top(), inter.right(), inter.bottom(), inter.left(),
				 inter.a(), inter.b(), inter.eigenvalue());
 
  residual_norm norm(sho, EPS);
  successive_overrelaxation sor(10000, inter.spectral_radius());

  int I = sho.I();
  int J = sho.J();
  int i,j;
  double norm0, norm1, ratio;	// initial norm, final norm, ratio
  int iter;

  norm0 = residual_norm::norm(sho);
  iter = sor.solve(sho, norm);
  norm1 = residual_norm::norm(sho);
  ratio = norm1/norm0;
  ostream& out = inter.output();

  out.precision(PRECISION);
  out << "# initial norm:\t" << norm0 << endl;
  out << "# final norm:\t" << norm1 << endl;
  out << "# ratio:\t" << ratio << endl;
  out << "# iterations:\t" << iter << endl;

  if(!inter.header())
    out << sho;

}
