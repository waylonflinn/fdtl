/* a problem resulting from finite differencing of Laplace's equation
 *
 */

#include "problem_basic.h"

class simple_harmonic_oscillator : public problem_basic
{
public:

  // constructors
  simple_harmonic_oscillator(
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
	  double eigenvalue);

  // methods
  double a(int i, int j) const { return 1;}
  double b(int i, int j) const { return 1;}
  double c(int i, int j) const { return rss;}
  double d(int i, int j) const { return rss;}
  double e(int i, int j) const 
    { return (mcx*i*i*ssx)+(mcy*j*j*ssy)- meig - ast;}
  double f(int i, int j) const { return 0;}

 private:
  double cx;
  double cy;
  double eig;
  // intermediates for e(int,int)
  double mcx;	// ssx*cx
  double mcy;	// ssx*cy
  double meig;	// ssx*eig

};
