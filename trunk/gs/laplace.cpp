#include <vector>
#include "../problem.cpp"
#include "../boundary.cpp"

/* a problem resulting from finite differencing of Laplace's equation
 *
 */

using std::vector;

class laplace : public problem
{
public:

  // methods
  double a(int i, int j) const { return 1;}
  double b(int i, int j) const { return 1;}
  double c(int i, int j) const { return 1;}
  double d(int i, int j) const { return 1;}
  double e(int i, int j) const { return 4;}
  double f(int i, int j) const { return 0;}
  double& u(int i, int j);	/* interface to the solution 
				   (returns a reference to a value) */
  boundary& top() const { return _top; }
  boundary& right() const { return _right; }
  boundary& bottom() const { return _bottom; }
  boundary& left() const { return _left; }

  // constructors
  laplace(int I,
	  int J,
	  boundary top,		// boundary objects for each boundary
	  boundary right,
	  boundary bottom,
	  boundary left);

private:
  vector< vector<double> > _solution;	// the solution
  int _I, _J;		// grid points in the width and height, resp.
  boundary _top, _right, _bottom, _left;	// boundaries

};

laplace::laplace(int I,
		 int J,
		 boundary top,
		 boundary right,
		 boundary bottom,
		 boundary left) 
  : _top(top), _right(right), _bottom(bottom), _left(left)
{
  int i;
  double average;

  average = 0;
  for(i = 0; i < _I; i++){
    average += top.value(i);
    average += bottom.value(i);
  }
  for(i = 0; i < _J; i++){
    average += right.value(i);
    average += left.value(i);
  }

  average = average / (2*I+2*J);

  _I = I;
  _J = J;

  _solution = vector< vector<double> >(I, vector<double>(J, average));
}

double& laplace::u(int i, int j)
{ return _solution[i][j]; }
