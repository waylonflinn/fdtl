
namespace option_set{

  const string NAME = "pde_prog";
  const string FIRST_VAR = "the first variable (x)";
  const string SEC_VAR = "the second variable (y)";

  const argument ARR_X[] =
    {argument("x0", "the mininum for " + FIRST_VAR),
     argument("x1", "the maximum for " + FIRST_VAR)};

  const argument ARR_Y[] =
    {argument("y0", "the mininum for " + SEC_VAR),
     argument("y1", "the maximum for " + SEC_VAR)};

  // command line options
  const argument INPUT = 
    argument("file", "a properly formatted file to use for the input (or '-').");

  const option OPT_I =
    option('I', argument("n", "the number of points for "+FIRST_VAR));

  const option OPT_J =
    option('J', argument("n", "the number of points for "+SEC_VAR));

  const option OPT_N =
    option('N', argument("n", "the number of points for both variables"));

  const option OPT_X = option('x', vector<argument>(ARR_X, ARR_X + 2));

  const option OPT_Y = option('y', vector<argument>(ARR_Y, ARR_Y + 2));

  const option OPT_D =
    option('d', "print only the hea(d)er information for the solution");

  const option ARR_OPT[] = {OPT_D, OPT_I, OPT_J, OPT_N, OPT_X, OPT_Y};

  const int SIZE = 6;
}
