#include <iostream>
#include <vector>
#include "interface_eig.h"
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
double eig(double eig1, double norm1, double eig2, double norm2);

main(int argc, char* argv[])
{
  interface_eig inter;

  try{
  inter = interface_eig("eig", argc, argv);
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

  double eig1, eig2, eig3;
  double a, b, parm;
  double num;
  a = 0.5;
  b = inter.anisotropy()*0.5;
  num = inter.number();
  if(num < 2){
    cerr << "invalid number of atoms entered." << endl;
    return 1;
  }

  parm = 4*M_PI*(num-1)*inter.scattering_length();
  if(inter.eigenvalue_present()){
    eig1 = inter.eigenvalue();
  }
  else{
    eig1 = 2*tf(parm, a, b);
  }
  eig2 = eig1*0.99;

  gross_pitaevskii gpe(inter.I(), inter.J(), inter.x(), inter.y(),
	     inter.top(), inter.right(), inter.bottom(), inter.left(),
	     a, b, eig1, parm);
  residual_norm norm(gpe, EPS);
  solution_norm_cyl<gross_pitaevskii> s_norm(gpe, EPS);
  gauss_seidel gs(1000);
  multigrid mlt(10000, inter.S(), gs);

  int I = gpe.I();
  int J = gpe.J();
  double norm0, norm1, ratio;	// initial norm, final norm, ratio
  double s_norm0, s_norm1, s_norm2, s_norm3;
  int iter;
  ostream& out = inter.output();
  double x0, x1, y0, y1;

  x0 = gpe.x0();
  y0 = gpe.y0();
  x1 = x0 + (gpe.dx()*gpe.I());
  y1 = y0 + (gpe.dy()*gpe.J());
  s_norm0 = solution_norm_cyl<gross_pitaevskii>::norm(gpe);
  norm0 = residual_norm::norm(gpe);
  iter = mlt.solve(gpe, norm);
  norm1 = residual_norm::norm(gpe);
  ratio = norm1/norm0;
  s_norm1 = solution_norm_cyl<gross_pitaevskii>::norm(gpe);

  gpe = gross_pitaevskii(inter.I(), inter.J(), inter.x(), inter.y(),
	     inter.top(), inter.right(), inter.bottom(), inter.left(),
	     a, b, eig2, parm);
  iter += mlt.solve(gpe, norm);
  s_norm2 = solution_norm_cyl<gross_pitaevskii>::norm(gpe);

  out << "# ("<< x0 << ", " << x1 << ") (" << y0 << ", " << y1 << ") " << endl;
  out << "# iterations:\t" << iter << endl;
  out << "# norm0:\t" << s_norm0 << endl;
  out << "# norm1, eig1:\t" << s_norm1 << ", " << eig1 << endl;
  out << "# norm2, eig2:\t" << s_norm2 << ", " << eig2 << endl;

  /* eigenvalue finding routine
   * fits norm(u)^2 (integral of u squared) as a function of eigenvalue
   * to a line and finds the intesection with norm(u)^2=1.
   * calculates new values and iterates to convergence.
   */
  int count = 3;
  while(((s_norm2-1) > EPS)&&count<10){
    // fit to a line and find the predicted eigenvalue
    eig3 = eig(eig1, s_norm1, eig2, s_norm2);

    gpe  = gross_pitaevskii(inter.I(), inter.J(), inter.x(), inter.y(),
			    inter.top(), inter.right(),
			    inter.bottom(), inter.left(),
			    a, b, eig3, parm);

    iter += mlt.solve(gpe, norm);	// solve new pde
    s_norm3 = solution_norm_cyl<gross_pitaevskii>::norm(gpe);
    out << "# norm"<<count<<", eig"<<count<<":\t";
    out << s_norm3 << ", " << eig3 << endl;
    s_norm1 = s_norm2;
    s_norm2 = s_norm3;
    eig1 = eig2;
    eig2 = eig3;
    count++;
  }

  out.precision(PRECISION);

  if(!inter.header())
    out << gpe;
  /*
  int i,j;
  int gy, gx;
  gx = trans_s.I();
  gy = trans_s.J();

  for(j = gy; j >= 0; --j){
    for(i = 0; i <= gx; ++i){
      out << trans_cyl.at(i, j) << " ";
    }
    out << endl;
  }
  */

}

/* fit to a line and find the intersection with norm(u)=1
 */
double eig(double eig1, double norm1, double eig2, double norm2)
{
  double a = (eig1-eig2)/(norm1 - norm2);
  double b = eig2 - (a*norm2);

  return a+b;
}

double tf(double k, double a, double b)
{
  return pow((2 * k)/( M_PI), 1.0/2.0) * pow((a*b), 1.0/4.0);
}
