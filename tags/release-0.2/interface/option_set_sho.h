#ifndef PDE_OPTION_SET_SHO
#define PDE_OPTION_SET_SHO

#include <vector>
#include "option.h"

namespace option_set_sho{
  const string FIRST_VAR = "the first variable (x)";
  const string SEC_VAR = "the second variable (y)";

  const option OPT_A =
    option('a', argument("w", "the coefficient to "+FIRST_VAR));

  const option OPT_B =
    option('b', argument("w", "the coefficient to "+SEC_VAR));
  
  const option OPT_EIG =
    option('e', argument("w", "the eigenvalue"));
  
  const option ARR_OPT[] =
    {OPT_A, OPT_B, OPT_EIG};

  const int SIZE = 3;
}

#endif	// PDE_OPTION_SET_SHO
