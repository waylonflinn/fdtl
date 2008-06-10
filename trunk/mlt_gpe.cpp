#include <iostream>
#include <vector>
#include "interface_mlt_gpe.h"
#include "gross_pitaevskii.h"
#include "gauss_seidel.h"
#include "multigrid.h"
#include "residual_norm.h"
#include "solution_norm_cyl.h"

#define PRECISION	3	// decimal digits to display
#define EPS		1.0e-4	// ratio of final residual to initial residual

using std::vector;
using std::cout;
using std::endl;

double tf(double k, double a, double b);

main(int argc, char* argv[])
{
  interface_mlt_gpe inter;

  try{
  inter = interface_mlt_gpe("mlt_gpe", argc, argv);
  }
  catch(invalid_argument e){
    cerr << e.what() << endl;
    return 1;
  }
  catch(help_exception){ return 0;}
  catch(...){
    cerr << "something bad happened!" << endl;
    return 1;
  }

  double eig;
  double a, b, parm;
  a = inter.a();
  b = inter.b();
  parm = inter.parameter();
  if(inter.eigenvalue_present())
    eig = inter.eigenvalue();
  else{
    eig = tf(parm, a, b);
    eig *= 2;
  }

  gross_pitaevskii gpe(inter.I(), inter.J(), inter.x(), inter.y(),
	     inter.top(), inter.right(), inter.bottom(), inter.left(),
	     a, b, eig, parm);
  residual_norm norm(gpe, EPS);
  solution_norm_cyl<gross_pitaevskii> s_norm(gpe, EPS);
  gauss_seidel gs(1000);
  multigrid mlt(10000, inter.S(), gs);

  int I = gpe.I();
  int J = gpe.J();
  double norm0, norm1, ratio;	// initial norm, final norm, ratio
  double s_norm0, s_norm1;
  int iter;
  ostream& out = inter.output();

  s_norm0 = solution_norm_cyl<gross_pitaevskii>::norm(gpe);
  norm0 = residual_norm::norm(gpe);
  iter = mlt.solve(gpe, norm);
  half_weighting hw;
  norm1 = residual_norm::norm(gpe);
  ratio = norm1/norm0;
  s_norm1 = solution_norm_cyl<gross_pitaevskii>::norm(gpe);

  out.precision(6);

  out << "# initial norm:\t" << norm0 << endl;
  out << "# final norm:\t" << norm1 << endl;
  out << "# ratio:\t" << ratio << endl;
  out << "# iterations:\t" << iter << endl;
  out << "# eigenvalue:\t" << eig << endl;
  out << "# init s norm:\t" << s_norm0 << endl;
  out << "# sol norm:\t" << s_norm1 << endl;

  out.precision(PRECISION);

  if(!inter.header())
    out << gpe;
}

double tf(double k, double a, double b)
{
  return pow((2 * k)/( M_PI), 1.0/2.0) * pow((a * b), 1.0/4.0);
}
