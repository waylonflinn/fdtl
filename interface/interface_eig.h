#ifndef PDE_INTERFACE_EIG
#define PDE_INTERFACE_EIG

#include "interface.h"
#include "option_set_eig.h"
#include "option_set_mlt.h"

class interface_eig : public interface
{
 public:

  // constants
  static const int DEF_I;
  static const int DEF_J;
  static const double DEF_L;
  static const double DEF_NUM;
  static const double DEF_SCAT;
  static const pair<double,double> DEF_X;
  static const pair<double,double> DEF_Y;

  static const int DEF_S;

  // constructors
  interface_eig(string id, int argc, char* argv[]);
  interface_eig();

  // methods
  // scaled anisotropy parameter (lambda squared)
  double anisotropy() const { return lam; }
  bool eigenvalue_present() const { return eig_pres; }
  double eigenvalue() const { return eig; }
  double number() const { return num; }
  double scattering_length() const { return scat; }
  int S() const { return gs; }

 protected:

  // variables
  double lam;
  double eig;
  double num;
  double scat;
  bool eig_pres;
  int gs;

  // methods

};

#endif	// PDE_INTERFACE_EIG
