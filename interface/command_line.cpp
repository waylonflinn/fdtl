/* parse a command line and print a usage statement
 * this class uses the 'iota' SGI algorithm
 */

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "option.cpp"
#include "next.cpp"

using std::vector;
using std::string;
using std::pair;
using std::map;

// exceptions
struct exception_argument {  };

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


  const pair<bool, string>& arg_val() const 
  { return arg_pair; }

  const string& usage();
  void parse(int argc, char* argv[]);

private:

  string prog_name;
  vector<option> opt_vec;
  argument arg;
  map<char, pair<bool, vector<string> > > opt_map;
  pair<bool, string> arg_pair;
  string use;
};

command_line::command_line(string name,
			   const vector<option>& option_vector,
			   const argument& argument)
  : opt_vec(option_vector), arg(argument), prog_name(name)
{
}

command_line::command_line() : opt_vec(), arg()
{
}

const string& command_line::usage()
{
  if((*this).use.size() == 0){
    (*this).use = prog_name + " <options> " + "<" + arg.name() + ">";

    (*this).use += "\n\twhere <options> is zero or more of:";

    vector<option>::iterator iter;
    for(iter = opt_vec.begin(); iter != opt_vec.end(); iter++){
      (*this).use += "\n" + (*iter).usage();
    }

    (*this).use += "\n\n\tand " + arg.usage();
  }

  return (*this).use;
}
/* throw an exception if there is not a one-to-one (but not necessarily onto)
 * mapping from the supplied command line arguments (in argv) to the expected
 * ones (this generally means an unrecognized argument was supplied
 * or a recognized one was supplied twice).
 */
void command_line::parse(int argc, char* argv[])
{
  if(argc < 1)
    return;

  vector<int> map_from(argc - 1, 0);

  generate(map_from.begin(), map_from.end(), next(1));

  vector<option>::iterator iter;
  for(iter = opt_vec.begin(); iter != opt_vec.end(); iter++){
    
  }
  
  if(map_from.size() > 0)
    throw exception_argument();
}

