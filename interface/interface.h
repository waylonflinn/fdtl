#ifndef PDE_INTERFACE
#define PDE_INTERFACE

#include <cerrno>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include "command_line.h"
#include "boundary.h"
#include "option_set.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;
using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;

struct help_exception{};

class interface
{
 public:

  // constants
  static const int DEF_I;
  static const int DEF_J;
  static const pair<double, double> DEF_X;
  static const pair<double, double> DEF_Y;

  // constructors
  interface(string id, int argc, char* argv[]);
  interface();

  // methods
  int I() const { return gx; }		// grid points in first var
  int J() const { return gy; }		// grid points in second var
  pair<double, double> x() const { return rx; }	// range of first var
  pair<double, double> y() const { return ry; }	// range of second var
  const boundary& top() const { return tp; }
  const boundary& right() const { return rt; }
  const boundary& bottom() const { return bt; }
  const boundary& left() const { return lf; }

  bool header() { return hdr; }
  ostream& output() const { return cout; }

 protected:

  // variables
  command_line cl;
  int gx;
  int gy;
  pair<double, double> rx;
  pair<double, double> ry;
  boundary tp;
  boundary rt;
  boundary bt;
  boundary lf;
  bool hdr;

  // methods
  int make_grid(char, int);
  pair<double, double> make_range(char, pair<double, double>);
  void make_bound();

};

#endif	// PDE_INTERFACE
