/* a problem representing a finite differencing of the Gross-Pitaevskii
 * equation (a modified schrodinger equation representing a many body
 * electrodynamic system) given in cylindrical coordinates.
 */

#include "problem_basic.h"

class gross_pitaevskii : public problem_basic
{
public:

  // constructors
  gross_pitaevskii(
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
	  double eigenvalue,
	  double parameter);

  // methods
  double a(int i, int j) const { return 1;}
  double b(int i, int j) const { return 1;}
  double c(int i, int j) const { return rss;}
  double d(int i, int j) const { return rss;}
  double e(int i, int j) const 
    { return (meig+ast+(p1x+(p2x*i)+(p3x*i*i))+(p1y+(p2y*j)+(p3y*j*j)));}
  double f(int i, int j) const { return 0;}

 private:
  double cx;
  double cy;
  double eig;
  double param;
  // intermediates for e(int,int)
  double meig;	// -1*ssx*eig
  double mparam;
  /* the following terms represent intermediate values in the computation
     of the potential term in the two variable */
  double p1x;	// sx^2*cx*x.first^2
  double p2x;	// 2*sx^3*cx*x.first
  double p3x;	// sx^4*cx
  double p1y;	// sx^2*cy*y.first^2
  double p2y;	// 2*sx^2*sy*cy*y.first
  double p3y;	// sx^2*sy^2*cy
  
};
