#include <iostream>
#include <vector>
#include "command_line.h"

using std::cout;
using std::endl;
using std::vector;

class interface {

  // constants
  static const int DEF_I = 20;
  static const int DEF_J = 20;
  static const pair<double, double> DEF_X;
  static const pair<double, double> DEF_Y;

  // constructors
  interface(int argc, char* argv[]);

  // methods
  int I();
  int J();
  pair<double, double> x();
  pair<double, double> y();
  ostream& output();
  istream& input();
};
