#include <stdlib.h>
#include <string>

class argument{

  /* Class for processing the command line arguments of the 'gs' class.
   *
   */
private:

  bool help;		// help requested
  bool calc_eig;	// calculate an initial eigenvalue
  
  double a, b, c;	/* the first, second, and third  potential
			   coefficients, resp. */
  double s;		// spectral radius of jacobi method 
  double k;		// interaction parameter
  double eig;		// initial eigenvalue
  double max_r;		// maximum r value
  double max_z;		// maximum z value
  int I;		// number of first argument grid points
  int J;		// number of second argument grid points
  std::string ifname;	// input file name
  std::string ofname;	// output file name

  void init();

public:

  const static double DEF_COEF = 0.5;

  const static double DEF_PARAM = 1.0;

  const static double DEF_R = 1.0;

  const static double DEF_Z = 2.0;

  const static int DEF_I = 20;

  const static int DEF_J = 20;

  argument();

  argument(int argc, char *argv[]);
  
  double first() const { return a; }

  double second() const { return b; }

  double third() const { return c; }

  double spectral_radius() const { return s; }

  double interaction() const { return k; }

  double eigenvalue() const { return eig; }

  double maximum_r() const { return max_r; }

  double maximum_z() const { return max_z; }

  int points_r() const { return I; }

  int points_z() const { return J; }

  bool calc_eigenvalue() const { return calc_eig; }

  std::string input_file() const { return ifname; }

  std::string output_file() const { return ofname; }

  bool help_requested() const { return help; }

};

argument::argument()
{
  this->init();
}

argument::argument(int argc, char *argv[])
{
  bool option;

  option = true;

  this->init();

  while(option && (argc > 1)) {
    if((*++argv)[0] == '-') {	// check the first char of the next arg
      --argc;
      switch ((*argv)[1]) {	// if '-' check the second char
      case 'o' :
	ofname += (*++argv);
	--argc;
	break;
      case 'a' :
	a = atof(*++argv);
	--argc;
	break;
      case 'b' :
	b = atof(*++argv);
	--argc;
	break;
      case 'c' :
	c = atof(*++argv);
	--argc;
	break;
      case 'r' :
	max_r = atof(*++argv);
	--argc;
	break;
      case 'z' :
	max_z = atof(*++argv);
	--argc;
	break;
      case 's' :
	s = atof(*++argv);
	--argc;
	break;
      case 'I' :
	I = atoi(*++argv);
	--argc;
	break;
      case 'J' :
	J = atoi(*++argv);
	--argc;
	break;
      case 'N' :
	I = J = atoi(*++argv);
	--argc;
	break;
      case 'e' :
	eig = atof(*++argv);
	calc_eig = false;
	--argc;
	break;
      case 'h' :
	help = true;
	break;
      }
    }
    else
      option = false;
  }
  if(argc > 1)
    ifname += (*argv);

}

void argument::init()
{
  help = false;
  calc_eig = true;
  s = 1.99;
  a = b = c = argument::DEF_COEF;
  k = argument::DEF_PARAM;
  max_r = argument::DEF_R;
  max_z = argument::DEF_Z;
  I = argument::DEF_I;
  J = argument::DEF_J;
}
