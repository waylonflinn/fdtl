/* an object represention a command line option.
 * construct with a letter (char) and one of:
 *	an argument
 *	a vector of arguments
 *	a description string, if the option takes no arguments
 */
#include <string>
#include <vector>
#include "argument.h"

using std::vector;
using std::string;

class option
{
public:
  // constants
  const static string PREFIX;	// identifies an option
  
  // constructors
  option(const char& letter, const argument& arg);
  option(const char& letter, const vector<argument>& argument_vector);
  option(const char& letter, const string& description);
  option();

  // methods
  char letter() const { return let; }
  int arg_count() const { return arg_vec.size(); }
  bool match(const vector<string>::iterator begin,
	     const vector<string>::iterator end);
  const string& usage();

private:
  char let;
  string desc;
  vector<argument> arg_vec;
  string use;
};
