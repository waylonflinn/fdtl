#ifndef PDE_INTERFACE_MLT
#define PDE_INTERFACE_MLT

#include "interface.h"
#include "option_set_mlt.h"

class interface_mlt : public interface
{
 public:

  // constants
  static const int DEF_I;
  static const int DEF_J;
  static const int DEF_S;

  // constructors
  interface_mlt(string id, int argc, char* argv[]);
  interface_mlt();

  // methods
  int S() const { return gs; }

 protected:

  // variables
  int gs;

  // methods

};

#endif	// PDE_INTERFACE_MLT
