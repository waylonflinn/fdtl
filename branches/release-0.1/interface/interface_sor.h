#ifndef PDE_INTERFACE_SOR
#define PDE_INTERFACE_SOR

#include "interface.h"
#include "option_set_sor.h"

class interface_sor : public interface
{
 public:

  // constants

  // constructors
  interface_sor(string id, int argc, char* argv[]);
  interface_sor();

  // methods
  double spectral_radius() const { return rad; }

 protected:
  // variables
  double rad;

  // methods

};

#endif	// PDE_INTERFACE_SOR
