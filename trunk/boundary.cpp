#include <vector>
/* boundary, class describing boundary conditions for a finite differenced pde
 *
 */

using namespace std;

class boundary
{
public:
  const static int DIRICHLET = 0;
  const static int NEUMANN = 1;

  // constructors
  boundary(int type, double value);
  boundary(int type,
	   vector<double>::iterator start,
	   vector<double>::iterator end);
  boundary(const boundary&);		// copy constructor

  ~boundary();				// destructor
  boundary& operator=(const boundary&);	// copy assignment

  const double& value(int i);

  int type() const { return _type; }	// type of boundary conditions

  const double& operator[](int i);

private:
  int _type;
  double _value;
  vector<double>* _p_value;
};

/* create a boundary condition of the given type with the given constant
 * value.
 */
boundary::boundary(int type, double value)
{
  _p_value = 0;
  _value = value;
  _type = type;
}

/* create a boundary condition of the given type with the values returned
 * by the given iterator pair.
 */
boundary::boundary(int type,
		   vector<double>::iterator start,
		   vector<double>::iterator end)
{
  _value = 0;
  _p_value = new vector<double>(start, end);
  _type = type;
}

boundary::boundary(const boundary& b)
{
  if(b._p_value == 0)
    _p_value = 0;
  else{
    _p_value = new vector<double>(b._p_value->begin(),
				b._p_value->end());
  }

  _value = b._value;
  _type = b._type;
}

boundary::~boundary()
{
  if(_p_value != 0)
    delete _p_value;
}

/* get the value at position i (zero based)
 */
const double& boundary::value(int i)
{ return (_p_value == 0) ? _value : (*_p_value)[i]; }

boundary& boundary::operator=(const boundary& b)
{
  if(_p_value != 0)
    delete _p_value;

  if(b._p_value == 0)
    _p_value = 0;
  else{
    _p_value = new vector<double>(b._p_value->begin(),
				b._p_value->end());
  }

  _value = b._value;
  _type = b._type;

}

/* subscript ([]) operator (synonym for value(int))
 */
const double& boundary::operator[](int i) 
{ return value(i); }
