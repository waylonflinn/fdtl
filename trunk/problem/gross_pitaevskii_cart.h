/* a problem representing a finite differencing of the Gross-Pitaevskii
 * equation (a modified schrodinger equation representing a many body
 * electrodynamic system) given in cartesian coordinates.
 */

#include "problem_basic.h"
#include "problem_resizable.h"

class gross_pitaevskii_cart : public problem_basic
{
public:

  gross_pitaevskii_cart();

  // constructors
  gross_pitaevskii_cart(
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
  double a(int i, int j) const { return 1.0;}
  double b(int i, int j) const { return 1.0;}
  double c(int i, int j) const { return rss;}
  double d(int i, int j) const { return rss;}
  double e(int i, int j) const 
    { return (meig+ast+(p1x+(p2x*i)+(p3x*i*i))+(p1y+(p2y*j)+(p3y*j*j)) +
	      mparm*sol[i-1][j-1]*sol[i-1][j-1]);}
  double f(int i, int j) const { return 0;}

  void eigenvalue(double eig);

  void grow(operator_prolong& op);
  void shrink(operator_restrict& op);
  gross_pitaevskii_cart clone();

 private:
  double x0;
  double y0;
  double cx;
  double cy;
  double eig;
  double parm;
  // intermediates for e(int,int)
  double meig;	// ssx*eig
  double mparm;	// -1*ssx*parm
  /* the following terms represent intermediate values in the computation
     of the potential term (which involves each variable squared) */
  double p1x;	// -1*ssx*cx*x.first^2
  double p2x;	// -1*ssx*cx*2*x.first*sx
  double p3x;	// -1*ssx*cx*ssx
  double p1y;	// -1*ssx*cy*y.first^2
  double p2y;	// -1*ssx*sy*2*cy*y.first*sy
  double p3y;	// -1*ssx*cy*ssy
  
};
