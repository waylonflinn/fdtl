/* a problem resulting from finite differencing of Laplace's equation
 *
 */

#include "problem_basic.h"
#include "problem_resizable.h"

class laplace : public problem_basic
{
public:


  // constructors
  laplace();

  laplace(int I,
	  int J,
	  pair<double, double> range_x,
	  pair<double, double> range_y,
	  const boundary& top,		// boundary objects for each boundary
	  const boundary& right,
	  const boundary& bottom,
	  const boundary& left);

  // methods
  double a(int i, int j) const { return 1;}
  double b(int i, int j) const { return 1;}
  double c(int i, int j) const { return rss;}
  double d(int i, int j) const { return rss;}
  double e(int i, int j) const { return ast;}
  double f(int i, int j) const { return 0;}

  void grow(operator_prolong& op);
  void shrink(operator_restrict& op);
  laplace clone();

};
