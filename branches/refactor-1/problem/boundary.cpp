#include <vector>
#include <iterator>
/* boundary, class describing boundary conditions for a finite differenced pde
 *
 */

using std::vector;

class boundary
{
public:
  // constants
  const static int DIRICHLET = 0;
  const static int NEUMANN = 1;

  // methods
  int type() const { return tp; }	// type of boundary conditions
  const double& value(int i);
  const double& operator[](int i);

  // constructors
  boundary(int type,
	   vector<double>::iterator start,
	   vector<double>::iterator end);

private:
  int tp;
  vector<double> val;

};

/* create a boundary condition of the given type with the values returned
 * by the given iterator pair.
 */
boundary::boundary(int type,
		   vector<double>::iterator start,
		   vector<double>::iterator end)
{
  val = vector<double>(start, end);
  tp = type;
}

/* get (a reference to) the value at position i (zero based)
 */
const double& boundary::value(int i)
{ return val[i]; }

/* subscript ([]) operator (synonym for value(int))
 */
const double& boundary::operator[](int i) 
{ return val[i]; }
