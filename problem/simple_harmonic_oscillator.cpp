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
    cx(coeff_x), cy(coeff_y), eig(eigenvalue), mcx(ssx*cx), mcy(ssy*cy),
    meig(ssx*eig)
        
{
  sol = vector< vector<double> >((*this).gx - 1,
                                 vector<double>((*this).gy - 1, 0.5));
}
