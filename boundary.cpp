#include <vector>
#include <iterator>
/* boundary, class describing boundary conditions for a finite differenced pde
 *
 */

using std::vector;

class boundary
{
public:
  const static int DIRICHLET = 0;
  const static int NEUMANN = 1;

  // constructors
  boundary(int type,
	   vector<double>::iterator start,
	   vector<double>::iterator end);

  const double& value(int i);

  int type() const { return _type; }	// type of boundary conditions

  const double& operator[](int i);

private:
  int _type;
  vector<double> _value;

};

/* create a boundary condition of the given type with the values returned
 * by the given iterator pair.
 */
boundary::boundary(int type,
		   vector<double>::iterator start,
		   vector<double>::iterator end)
{
  _value = vector<double>(start, end);
  _type = type;
}

/* get the value at position i (zero based)
 */
const double& boundary::value(int i)
{ return _value[i]; }

/* subscript ([]) operator (synonym for value(int))
 */
const double& boundary::operator[](int i) 
{ return _value[i]; }
