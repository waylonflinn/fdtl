#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "command_line.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::ostream;
using std::ofstream;
using std::ifstream;

class interface
{
 public:

  // constants
  static const int DEF_I;
  static const int DEF_J;
  static const pair<double, double> DEF_X;
  static const pair<double, double> DEF_Y;

  /* these constants represent the command line for this interface */
  static const string NAME;	// name of the program
  static const argument INPUT;	// input file
  static const option OPT_I;
  static const option OPT_J;
  static const option OPT_X;
  static const option OPT_Y;

  // constructors
  interface(string id, int argc, char* argv[]);
  interface();

  // methods
  int I() const { return gx; }		// grid points in first var
  int J() const { return gy; }		// grid points in second var
  pair<double, double> x() const { return rx; }	// range of first var
  pair<double, double> y() const { return ry; }	// range of second var
  ostream& output();	// output
  vector< vector<double> > boundary();

 protected:
  // constants
  static const string FIRST_VAR;
  static const string SEC_VAR;
  static const argument ARR_X[];
  static const argument ARR_Y[];
  static const option ARR_OPT[];

  // variables
  command_line cl;
  int gx;
  int gy;
  pair<double, double> rx;
  pair<double, double> ry;

  // methods
  int grid_opt(char);
  pair<double, double> range_opt(char);

};
