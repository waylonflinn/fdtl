#ifndef PDE_OPTION_SET_GPE
#define PDE_OPTION_SET_GPE

#include <vector>
#include "option.h"

namespace option_set_gpe{
  const string FIRST_VAR = "the first variable (x)";
  const string SEC_VAR = "the second variable (y)";

  const option OPT_A =
    option('a', argument("w", "the coefficient to "+FIRST_VAR));

  const option OPT_B =
    option('b', argument("w", "the coefficient to "+SEC_VAR));
  
  const option OPT_EIG =
    option('e', argument("w", "the eigenvalue"));

  const option OPT_PARM =
    option('k', argument("w", "the interaction parameter"));
  
  const option ARR_OPT[] =
    {OPT_A, OPT_B, OPT_EIG, OPT_PARM};

  const int SIZE = 4;
}

#endif	// PDE_OPTION_SET_GPE
