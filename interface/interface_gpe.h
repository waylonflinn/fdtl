#ifndef PDE_INTERFACE_GPE
#define PDE_INTERFACE_GPE

#include "interface.h"
#include "option_set_gpe.h"

class interface_gpe : public interface
{
 public:

  // constants
  static const double DEF_A;
  static const double DEF_B;
  static const double DEF_PARM;
  static const pair<double,double> DEF_X;
  static const pair<double,double> DEF_Y;

  // constructors
  interface_gpe(string id, int argc, char* argv[]);
  interface_gpe();

  // methods
  double a() const { return cx; }
  double b() const { return cy; }
  bool eigenvalue_present() const { return eig_pres; }
  double eigenvalue() const { return eig; }
  double parameter() const { return parm; }

 protected:

  // variables
  double cx;
  double cy;
  double eig;
  double parm;
  bool eig_pres;

  // methods

};

#endif	// PDE_INTERFACE_GPE
