
namespace option_set_sor{
  const option OPT_R =
    option('r', 
	   argument("w", "the spectral radius of the Jacobi method"));

  const option ARR_OPT[] = {OPT_R};

  const int SIZE = 1;
}
