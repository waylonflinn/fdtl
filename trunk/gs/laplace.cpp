#include "../problem.cpp"
#include "../boundary.cpp"

/* a problem resulting from finite differencing of Laplace's equation
 *
 */

class laplace : public problem
{
public:

  double a(int i, int j) const { return 1;}
  double b(int i, int j) const { return 1;}
  double c(int i, int j) const { return 1;}
  double d(int i, int j) const { return 1;}
  double e(int i, int j) const { return 4;}
  double f(int i, int j) const { return 0;}
  double& u(int i, int j);	/* interface to the solution 
				   (returns a reference) */

  laplace(int I,
	  int J,
	  boundary top,		// boundary objects for each boundary
	  boundary right,
	  boundary bottom,
	  boundary left);

  laplace(laplace& l);		// copy constructor

  ~laplace();			// destructor

  laplace& operator=(const laplace& l);	// copy assignment

private:
  vector< vector<double> >* _p_solution;	// pointer to the solution
  int _I, _J;
  boundary _top, _right, _bottom, _left;

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

  _p_solution = new vector< vector<double> >(I, vector<double>(J, average));
}

laplace::laplace(laplace& l)
  : _top(l._top), _right(l._right), _bottom(l._bottom), _left(l._left)
{
  int i;
  double average;

  _I = l._I;
  _J = l._J;

  _p_solution = new vector< vector<double> >(_I, vector<double>(_J, 0));

  for(i = 0; i < _I; ++i){
    _p_solution[i] = vector<double>(l._p_solution[i].begin(),
				    l._p_solution[i].end());
  }
}

laplace::~laplace()
{
  delete _p_solution;
}

laplace& laplace::operator=(const laplace& l)
{
  int i;
  double average;

  _I = l._I;
  _J = l._J;
  _top = l._top;
  _right = l._right;
  _bottom = l._bottom;
  _left = l._left;

  delete _p_solution;
  _p_solution = new vector< vector<double> >(_I, vector<double>(_J, 0));

  for(i = 0; i < _I; ++i){
    _p_solution[i] = vector<double>(l._p_solution[i].begin(),
				    l._p_solution[i].end());
}

double& laplace::u(int i, int j)
{ return (*_p_solution)[i][j]; }
