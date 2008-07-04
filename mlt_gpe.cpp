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
  // create the interface object for this executable
  interface_mlt_gpe inter;

  // process the command line arguments using the interface object
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

  // if an eigenvalue was supplied use it
  if(inter.eigenvalue_present())
    eig = inter.eigenvalue();
  else // otherwise use the thomas-fermi approximation
  {
    eig = tf(parm, a, b);
    eig *= 2;
  }

  // create the problem definition
  gross_pitaevskii gpe(inter.I(), inter.J(), inter.x(), inter.y(),
	     inter.top(), inter.right(), inter.bottom(), inter.left(),
	     a, b, eig, parm);

  // create the goal (based on residual: a measure of error)
  residual_norm norm(gpe, EPS);

  // create a second goal (not used)
  //solution_norm_cyl<gross_pitaevskii> s_norm(gpe, EPS);

  // create the smoother (a simple solver)
  gauss_seidel gs(1000);

  // create the multigrid solver using the simple solver
  multigrid mlt(10000, inter.S(), gs);

  int I = gpe.I();
  int J = gpe.J();
  double norm0, norm1, ratio;	// initial norm, final norm, ratio
  double s_norm0, s_norm1;
  int iter;
  ostream& out = inter.output();

  // calculate initial norm and residual for later display
  s_norm0 = solution_norm_cyl<gross_pitaevskii>::norm(gpe);
  norm0 = residual_norm::norm(gpe);

  // solve the problem
  iter = mlt.solve(gpe, norm);

  //half_weighting hw;

  // calculate final norm, residual and ratio of norms for later display
  norm1 = residual_norm::norm(gpe);
  ratio = norm1/norm0;
  s_norm1 = solution_norm_cyl<gross_pitaevskii>::norm(gpe);

  out.precision(6);

  // print header information
  out << "# initial norm:\t" << norm0 << endl;
  out << "# final norm:\t" << norm1 << endl;
  out << "# ratio:\t" << ratio << endl;
  out << "# iterations:\t" << iter << endl;
  out << "# eigenvalue:\t" << eig << endl;
  out << "# init s norm:\t" << s_norm0 << endl;
  out << "# sol norm:\t" << s_norm1 << endl;

  out.precision(PRECISION);

  // print solution
  if(!inter.header())
    out << gpe;
}

/* calculate the thomas-fermi approximation for the equation with the given
 * interaction parameter and coefficients. 
 */
double tf(double k, double a, double b)
{
  return pow((2 * k)/( M_PI), 1.0/2.0) * pow((a * b), 1.0/4.0);
}
