#include <iostream>
#include <vector>
#include "interface.h"
#include "laplace.h"
#include "solution_norm_cyl.h"

#define PRECISION	5	// decimal digits to display
#define EPS		1.0e-5	// ratio of final residual to initial residual

using std::vector;
using std::cout;
using std::endl;

double x_0;
double y_0;
double dx;
double dy;
double t_x(int);
double t_y(int);
int main(int argc, char* argv[])
{
  interface inter;

  try{
  inter = interface("gs_l", argc, argv);
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

  laplace lp(inter.I(), inter.J(), inter.x(), inter.y(),
	     inter.top(), inter.right(), inter.bottom(), inter.left());

  int I,J;
  int i,j;
  double norm0;
  ostream& out = cout;

  I = lp.I();
  J = lp.J();
  x_0 = lp.x0();
  y_0 = lp.y0();
  dx = lp.dx();
  dy = lp.dy();
  double x,y;
  for(i = 1; i < I; i++)
    for(j = 1; j < J; j++){
      x = t_x(i);
      y = t_y(j);
      lp.u(i,j) = exp(-(x*x + y*y));
    }

  norm0 = solution_norm_cyl::norm(lp);

  out.precision(15);

  out << "# norm:\t" << norm0 << endl;

  out.precision(PRECISION);
  
  if(!inter.header())
    out << lp;

  return 0;
}

double t_y(int j)	// transform to y
{ return (y_0 + (j*dy)); }

double t_x(int i)	// transform to x
{ return (x_0 + (i*dx)); }
