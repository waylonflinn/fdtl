#include <iostream>
#include <vector>
#include "interface_mlt_gpe_cart.h"
#include "gross_pitaevskii_cart.h"
#include "gauss_seidel.h"
#include "multigrid.h"
#include "residual_norm.h"
#include "solution_norm.h"

#define PRECISION	3	// decimal digits to display
#define EPS		1.0e-4	// ratio of final residual to initial residual

using std::vector;
using std::cout;
using std::endl;

double tf(double k, double a, double b);

main(int argc, char* argv[])
{
  interface_mlt_gpe_cart inter;

  try{
  inter = interface_mlt_gpe_cart("eig_cart", argc, argv);
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

  double tf_eig, eig1;
  double a, b, parm;
  a = inter.a();
  b = inter.b();
  parm = inter.parameter();
  if(inter.eigenvalue_present()){
    tf_eig = tf(parm, a, b);
    eig1 = inter.eigenvalue();
    }
  else{
    tf_eig = tf(parm, a, b);
    eig1 = tf_eig*2;
  }

  gross_pitaevskii_cart gpe(inter.I(), inter.J(), inter.x(), inter.y(),
	     inter.top(), inter.right(), inter.bottom(), inter.left(),
	     a, b, eig1, parm);
  residual_norm res(gpe, EPS);
  solution_norm s_norm(gpe, EPS);
  gauss_seidel gs(1000);
  multigrid mlt(10000, inter.S(), gs);

  int I = gpe.I();
  int J = gpe.J();
  double res0, res1, ratio;	// initial norm, final norm, ratio
  double norm0, norm1;
  int iter;
  ostream& out = inter.output();

  norm0 = solution_norm::norm(gpe);
  res0 = residual_norm::norm(gpe);
  iter = mlt.solve(gpe, res);
  res1 = residual_norm::norm(gpe);
  ratio = res1/res0;
  norm1 = solution_norm::norm(gpe);

  out << "# init res:\t" << res0 << endl;
  out << "# fin res:\t" << res1 << endl;
  out << "# ratio:\t" << ratio << endl;
  out << "# iterations:\t" << iter << endl;
  out << "# tf:\t" << tf_eig << endl;
  out << "# init norm:\t" << norm0 << endl;
  out << "# fin norm:\t" << norm1 << endl;

  out.precision(PRECISION);

  if(!inter.header())
    out << gpe;
}

double tf(double k, double a, double b)
{
  return pow((2 * k)/( M_PI), 1.0/2.0) * pow((a*b), 1.0/4.0);
}
