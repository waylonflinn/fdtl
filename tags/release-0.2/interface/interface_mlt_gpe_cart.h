#ifndef PDE_INTERFACE_MLT_GPE_CART
#define PDE_INTERFACE_MLT_GPE_CART

#include "interface.h"
#include "option_set_gpe.h"
#include "option_set_mlt.h"

class interface_mlt_gpe_cart : public interface
{
 public:

  // constants
  static const int DEF_I;
  static const int DEF_J;
  static const double DEF_A;
  static const double DEF_B;
  static const double DEF_PARM;
  static const pair<double,double> DEF_X;
  static const pair<double,double> DEF_Y;

  static const int DEF_S;

  // constructors
  interface_mlt_gpe_cart(string id, int argc, char* argv[]);
  interface_mlt_gpe_cart();

  // methods
  double a() const { return cx; }
  double b() const { return cy; }
  bool eigenvalue_present() const { return eig_pres; }
  double eigenvalue() const { return eig; }
  double parameter() const { return parm; }
  int S() const { return gs; }

 protected:

  // variables
  double cx;
  double cy;
  double eig;
  double parm;
  bool eig_pres;
  int gs;

  // methods

};

#endif	// PDE_INTERFACE_MLT_GPE_CART
