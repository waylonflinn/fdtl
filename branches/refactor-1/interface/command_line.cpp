/* parse a command line and print a usage statement
 */

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "option.cpp"

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
/* throw an exception if an element in the set of supplied command line
 * arguments (in argv) is not mapped to the set of expected ones.
 * this generally means an  unrecognized argument was supplied or not
 * enough arguments followed an  option to satisfy it's argument requirements.
 */
void command_line::parse(int argc, char* argv[])
{
  if(argc < 1)
    return;

  bool found;
  vector<string> user_arg(argv + 1, argv + argc);// user supplied arguments

  vector<option>::iterator opt_iter = opt_vec.begin();
  for( ; opt_iter != opt_vec.end(); opt_iter++){

    found = false;

    // go backwards so as not to invalidate the iterators on erasure
    vector<string>::iterator user_iter = user_arg.end() - 1;
    while(!found && (user_iter != user_arg.begin() - 1)){
      if((*opt_iter).match(*user_iter)) {
      
	found = true;
	int count = ((*opt_iter).arg_count() + 1);
        
	if(user_arg.size() < count) 
	  throw exception_argument();
      
	vector<string>::iterator end_iter = user_iter + count;
	opt_map[(*opt_iter).letter()] =
	  pair<bool, vector<string> >(true,
				      vector<string>(user_iter, end_iter));
	user_arg.erase(user_iter, end_iter);
      }
      user_iter--;
    }
    if(!found)
      opt_map[(*opt_iter).letter()] =
	pair<bool, vector<string> >(false, vector<string>());
  }
  
  if(user_arg.size() > 0)	// leftovers
    throw exception_argument();
}
