/* a partial implementation of the abstract problem class which provides
 * an implementation of all virtual methods except those describing the
 * coefficients of the finite-differenced equation.
 * it allows only square boundaries and uses vectors to implement the solution.
 */

#ifndef PDE_PROBLEM_BASIC
#define PDE_PROBLEM_BASIC

#include <ostream>
#include <vector>
#include <utility>
#include "problem.h"
#include "boundary.h"

using std::vector;
using std::pair;
using std::ostream;
using std::endl;

class problem_basic : public problem
{
public:

  // constructors
  problem_basic();

  problem_basic(int I,
		int J,
		pair<double, double> range_x,
		pair<double, double> range_y,
		const boundary& top,
		const boundary& right,
		const boundary& bottom,
		const boundary& left);

  // methods
  int I() const { return gx; }
  int J() const { return gy; }
  double dx() const {return sx; }
  double dy() const { return sy;}
  double& u(int i, int j);	/* interface to interior values
				   (returns a reference to a value) */
  double at(int i, int j) const;	// correct boundary values and checking

  const boundary& top() const { return tp; }
  const boundary& right() const { return rt; }
  const boundary& bottom() const { return bt; }
  const boundary& left() const { return lf; }

  ostream& put(ostream& s) const;

protected:
  vector< vector<double> > sol;	// the solution
  int gx, gy;	// grid points in the first (i) and second (j) variables, resp
  double sx, sy;	// grid spacing in the first and second variables, resp
  pair<double, double> x, y;	// ranges for first and second vars, resp
  boundary tp, rt, bt, lf;	// boundaries, resp.; top, right, bottom, left
  // intermediate calc terms
  double ssx, ssy;	// spacings squared; sx*sx, sy*sy
  double rss;		// ratio of the squared spacings ssx/ssy
  double ast;		// assymetric term -2*(1+rss)

};

ostream& operator<<(ostream& s, const problem_basic& prob);

#endif	// PDE_PROBLEM_BASIC
