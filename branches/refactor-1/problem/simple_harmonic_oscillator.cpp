#include "simple_harmonic_oscillator.h"

simple_harmonic_oscillator::simple_harmonic_oscillator(
	  int I,
	  int J,
	  pair<double, double> range_x,
	  pair<double, double> range_y,
	  const boundary& top,		// boundary objects for each boundary
	  const boundary& right,
	  const boundary& bottom,
	  const boundary& left,
	  double coeff_x,
	  double coeff_y,
	  double eigenvalue)
  : problem_basic(I, J, range_x, range_y, top, right, bottom, left),
    cx(coeff_x), cy(coeff_y), eig(eigenvalue),
    p1x(ssx*cx*x.first*x.first), p2x(2*ssx*sx*cx*x.first), p3x(ssx*ssx*cx),
    p1y(ssx*cy*y.first*y.first), p2y(2*ssx*sy*cy*y.first), p3y(ssx*ssy*cy),
    meig(-1*ssx*eig)
        
{
  double norm_av = 1/(2.0*(x.second-x.first)+2.0*(x.second-x.first));

  sol = vector< vector<double> >((*this).gx - 1,
                                 vector<double>((*this).gy - 1, norm_av));
}
