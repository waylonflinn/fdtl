/* a problem resulting from finite differencing of Laplace's equation
 *
 */

#include "problem_basic.h"

class laplace : public problem_basic
{
public:

  // constructors
  laplace(int I,
	  int J,
	  double range_x,
	  double range_y,
	  const boundary& top,		// boundary objects for each boundary
	  const boundary& right,
	  const boundary& bottom,
	  const boundary& left);

  // methods
  double a(int i, int j) const { return 1;}
  double b(int i, int j) const { return 1;}
  double c(int i, int j) const { return 1;}
  double d(int i, int j) const { return 1;}
  double e(int i, int j) const { return -4;}
  double f(int i, int j) const { return 0;}

};
