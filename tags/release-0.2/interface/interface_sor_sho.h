#ifndef PDE_INTERFACE_SHO
#define PDE_INTERFACE_SHO

#include "interface.h"
#include "option_set_sho.h"
#include "option_set_sor.h"

class interface_sor_sho : public interface
{
 public:

  // constants
  static const double DEF_A;
  static const double DEF_B;
  static const double DEF_EIG;
  static const pair<double,double> DEF_X;
  static const pair<double,double> DEF_Y;

  // constructors
  interface_sor_sho(string id, int argc, char* argv[]);
  interface_sor_sho();

  // methods
  double a() const { return cx; }
  double b() const { return cy; }
  double eigenvalue() const { return eig; }
  double spectral_radius() const { return rad; }

 protected:
  // variables
  double cx;
  double cy;
  double eig;
  double rad;

  // methods

};

#endif	// PDE_INTERFACE_SHO
