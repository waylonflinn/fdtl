/* parse a command line and print a usage statement
 * automatically supply a help option with '-h'
 */

#ifndef PDE_COMMAND_LINE
#define PDE_COMMAND_LINE

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <stdexcept>
#include <algorithm>
#include "option.h"

using std::vector;
using std::string;
using std::pair;
using std::map;
using std::invalid_argument;

class command_line {
public:
  // constants
  
  // constructors
  command_line(string name,
	       const vector<option>& option_vector,
	       const argument& argument);
  command_line();

  // methods
  const pair<bool, vector<string> >& operator[](const char& letter)
  { return opt_map[letter]; }


  const string& arg_val() const 
  { return arg_string; }

  const string& usage();
  void parse(int argc, char* argv[]);

private:

  option help;
  string prog_name;
  vector<option> opt_vec;
  argument arg;
  mutable map<char, pair<bool, vector<string> > > opt_map;
  string arg_string;
  mutable string use;
};

#endif	//PDE_COMMAND_LINE
