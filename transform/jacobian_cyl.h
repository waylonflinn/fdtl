/* a transformation resulting from the multiplication of a problem
 * by the jacobian for cylidrical coordinates (r*sin(theta)), where
 * the problem has cylindrical (theta) symmetry and the jacobian becomes
 * r*2*PI (PI here *is* the ubiquitious constant relating the diameter of
 * a circle to it's circumference).
 * the template type for this class is the 'Static Solution' which will be
 * transformed.
 */ 

#ifndef PDE_JACOBIAN_CYL
#define PDE_JACOBIAN_CYL

#include <cmath>

template<class StaticSolution>
class jacobian_cyl {

 public:
  jacobian_cyl(const StaticSolution& solution);

  int I() const {return sol.I();}
  int J() const {return sol.J();}
  double dx() const {return sol.dx();}
  double dy() const {return sol.dy();}
  double x0() const {return sol.x0();}
  double y0() const {return sol.y0();}
  double at(int i, int j) const;

 private:
  StaticSolution sol;

};

template <class StaticSolution>
jacobian_cyl<StaticSolution>::jacobian_cyl(const StaticSolution& solution) : sol(solution)
{
}

template <class StaticSolution>
double jacobian_cyl<StaticSolution>::at(int i, int j) const
{
  return sol.at(i,j)*2*M_PI*(sol.x0()+(sol.dx()*i));
}

#endif	// PDE_JACOBIAN_CYL
