/* a transformation equivalent to taking the gradient of a solution,
 * and finding the squared norm of the result.
 * the template type for this class is the 'Static Solution' which will be
 * transformed.
 */ 

#ifndef PDE_GRADIENT_NORM_SQUARED
#define PDE_GRADIENT_NORM_SQUARED

#include <cmath>

template<class StaticSolution>
class gradient_norm_squared {

 public:
  gradient_norm_squared(const StaticSolution& solution);

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
gradient_norm_squared<StaticSolution>::gradient_norm_squared<StaticSolution>(const StaticSolution& solution) : sol(solution)
{
}

template <class StaticSolution>
double gradient_norm_squared<StaticSolution>::at(int i, int j) const
{
  return (((sol.at(i+1,j)*sol.at(i+1,j))-
	   (2*sol.at(i+1,j)*sol.at(i-1,j))+
	   (sol.at(i-1,j)*sol.at(i-1,j)))/(4*sol.dx()*sol.dx())) +
    (((sol.at(i,j+1)*sol.at(i,j+1))-
      (2*sol.at(i,j+1)*sol.at(i,j-1))+
      (sol.at(i,j-1)*sol.at(i,j-1)))/(4*sol.dy()*sol.dy()));
}

#endif	// PDE_GRADIENT_NORM_SQUARED
