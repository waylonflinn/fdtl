#include <vector>
#include "problem.cpp"
#include "boundary.cpp"

/* a problem resulting from finite differencing of Laplace's equation
 *
 */

using std::vector;

class laplace : public problem
{
public:

  // methods
  int I() const { return ig; }
  int J() const { return jg; }
  double a(int i, int j) const { return 1;}
  double b(int i, int j) const { return 1;}
  double c(int i, int j) const { return 1;}
  double d(int i, int j) const { return 1;}
  double e(int i, int j) const { return 4;}
  double f(int i, int j) const { return 0;}
  double& u(int i, int j);	/* interface to the solution 
				   (returns a reference to a value) */
  const boundary& top() const { return tp; }
  const boundary& right() const { return rt; }
  const boundary& bottom() const { return bt; }
  const boundary& left() const { return lf; }

  // constructors
  laplace(int I,
	  int J,
	  const boundary& top,		// boundary objects for each boundary
	  const boundary& right,
	  const boundary& bottom,
	  const boundary& left);

private:
  vector< vector<double> > sol;	// the solution
  int ig, jg;		// grid points in the width (i) and height (j), resp.
  boundary tp, rt, bt, lf;	// boundaries, resp.; top, right, bottom, left

};

laplace::laplace(int I,
		 int J,
		 const boundary& top,
		 const boundary& right,
		 const boundary& bottom,
		 const boundary& left) 
  : ig(I), jg(J), tp(top), rt(right), bt(bottom), lf(left)
{
  int i;
  double average;

  average = 0;
  for(i = 0; i < (*this).ig; i++){
    average += (*this).tp.value(i);
    average += (*this).bt.value(i);
  }
  for(i = 0; i < (*this).jg; i++){
    average += (*this).rt.value(i);
    average += (*this).lf.value(i);
  }

  average = average / ((2*(*this).ig)+(2*(*this).jg));

  sol = vector< vector<double> >((*this).ig,
				 vector<double>((*this).jg, average));
}

double& laplace::u(int i, int j)
{ return sol[i][j]; }
