#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "command_line.h"

using std::cout;
using std::endl;
using std::vector;
using std::ostream;

class interface
{
 public:

  // constants
  static const int DEF_I;
  static const int DEF_J;
  static const pair<double, double> DEF_X;
  static const pair<double, double> DEF_Y;

  static const command_line CL;

  // constructors
  interface(string id, int argc, char* argv[]);

  // methods
  int I();
  int J();
  pair<double, double> x();
  pair<double, double> y();
  ostream& output();
  vector< vector<double> > boundary();

 protected:
  // constants
  static const string NAME;
  static const argument INPUT;
  static const option OPT_I;
  static const option OPT_J;
  static const option OPT_X;
  static const option OPT_Y;

  static const string FIRST_VAR;
  static const string SEC_VAR;
  const static argument ARR_X[];
  const static argument ARR_Y[];
  const static option ARR_OPT[];

  // variables
  int gx;
  int gy;
  pair<double, double> rx;
  pair<double, double> ry;
  ostream out;
};
