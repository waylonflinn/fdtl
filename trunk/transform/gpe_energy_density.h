/* a transformation equivalent to taking the gradient of a solution,
 * and finding the squared norm of the result.
 * the template type for this class is the 'GPE Solution' which will be
 * transformed.
 */ 

#ifndef PDE_GPE_ENERGY_DENSITY
#define PDE_GPE_ENERGY_DENSITY

#include <cmath>
#include "gradient_norm_squared.h"

template<class GPESolution>
class gpe_energy_density {

 public:
  gpe_energy_density(const GPESolution& solution);

  int I() const {return sol.I();}
  int J() const {return sol.J();}
  double dx() const {return sol.dx();}
  double dy() const {return sol.dy();}
  double x0() const {return sol.x0();}
  double y0() const {return sol.y0();}
  double at(int i, int j) const;

 private:
  GPESolution sol;
  gradient_norm_squared<GPESolution> gns;
};

template <class GPESolution>
gpe_energy_density<GPESolution>::gpe_energy_density<GPESolution>(const GPESolution& solution) :
  sol(solution), gns(solution)
{
}

template <class GPESolution>
double gpe_energy_density<GPESolution>::at(int i, int j) const
{
  double sol_val = sol.at(i,j);
  double sol_val_s = sol_val*sol_val;
  double r = sol.r(i);
  double z = sol.z(j);
  double pot = (sol.r_coefficient()*r*r)+(sol.z_coefficient()*z*z);
  
  return ((0.5*gns.at(i,j)) +
	      (pot*sol_val_s) +
	  (0.5*sol.interaction_parameter()*sol_val_s*sol_val_s));
}

#endif	// PDE_GPE_ENERGY_DENSITY
