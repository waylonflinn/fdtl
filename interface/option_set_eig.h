#ifndef PDE_OPTION_SET_EIG
#define PDE_OPTION_SET_EIG

#include <vector>
#include "option.h"

namespace option_set_eig{
  const string FIRST_VAR = "the first variable (x)";
  const string SEC_VAR = "the second variable (y)";

  const option OPT_L =
    option('l', argument("w", "the coefficent to " + SEC_VAR));
  
  const option OPT_EIG =
    option('e', argument("w", "the eigenvalue"));

  const option OPT_NUM =
    option('n', argument("w", "the number of atoms"));

  const option OPT_SCAT =
    option('a', argument("w", "the (scaled) scattering length"));
  
  const option ARR_OPT[] =
    {OPT_L, OPT_EIG, OPT_NUM, OPT_SCAT};

  const int SIZE = 4;
}

#endif	// PDE_OPTION_SET_EIG
