/* boundary, class describing boundary conditions for a finite differenced pde
 *
 */

#ifndef PDE_BOUNDARY
#define PDE_BOUNDARY

#include <vector>
#include <iterator>

using std::vector;

class boundary
{
public:
  // constants
  const static int DIRICHLET = 0;	// value of function specified
  const static int NEUMANN = 1;		// value of derivative specified

  // methods
  int type() const { return tp; }	// type of boundary conditions
  double at(int i) const; 	// value at i
  double& operator[](int i);	// synonym for value

  // constructors

  /* create a boundary condition of the given type with the values returned
   * by the given iterator pair.
   */
  boundary(int type,
	   vector<double>::iterator start,
	   vector<double>::iterator end);

private:
  int tp;				// type
  vector<double> val;

};

#endif	// PDE_BOUNDARY
