#include "interface.h"

class interface_sho : public interface
{
 public:

  // constants
  static const double DEF_A;
  static const double DEF_B;
  static const double DEF_EIG;
  static const pair<double,double> DEF_X;
  static const pair<double,double> DEF_Y;

  /* these constants represent the command line for this interface */
  static const option OPT_A;
  static const option OPT_B;
  static const option OPT_EIG;

  // constructors
  interface_sho(string id, int argc, char* argv[]);
  interface_sho();

  // methods
  double a() const { return cx; }
  double b() const { return cy; }
  double eigenvalue() const { return eig; }

 protected:
  // constants
  static const option ARR_OPT_SHO[];

  // variables
  double cx;
  double cy;
  double eig;

  // methods

};
