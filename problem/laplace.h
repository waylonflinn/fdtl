#include <vector>
#include "problem.h"
#include "boundary.h"

/* a problem resulting from finite differencing of Laplace's equation
 *
 */

using std::vector;

class laplace : public problem
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
  int I() const { return gx; }
  int J() const { return gy; }
  double dx() const {return sx; }
  double dy() const { return sy;}
  double a(int i, int j) const { return 1;}
  double b(int i, int j) const { return 1;}
  double c(int i, int j) const { return 1;}
  double d(int i, int j) const { return 1;}
  double e(int i, int j) const { return -4;}
  double f(int i, int j) const { return 0;}
  double& u(int i, int j);	/* interface to interior values
				   (returns a reference to a value) */
  double at(int i, int j) const;	// correct boundary values and checking

  const boundary& top() const { return tp; }
  const boundary& right() const { return rt; }
  const boundary& bottom() const { return bt; }
  const boundary& left() const { return lf; }

private:
  vector< vector<double> > sol;	// the solution
  int gx, gy;	// grid points in the first (i) and second (j) variables, resp
  double sx, sy;	// grid spacing in the first and second variables, resp
  boundary tp, rt, bt, lf;	// boundaries, resp.; top, right, bottom, left

};
