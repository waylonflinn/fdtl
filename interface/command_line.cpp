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
/* throw an exception if an element in the set of supplied command line
 * arguments (in argv) is not mapped to the set of expected ones.
 * this generally means an
 * unrecognized argument was supplied or not enough arguments followed an
 * option to satisfy it's argument requirements.
 */
void command_line::parse(int argc, char* argv[])
{
  if(argc < 1)
    return;

  vector<int> map_from(argc - 1, 0);

  generate(map_from.begin(), map_from.end(), next(1));

  vector<option>::iterator iter;
  for(iter = opt_vec.begin(); iter != opt_vec.end(); iter++){

    // go backwards so as not to invalidate the iterators on erasure
    vector<int>::iterator in_iter;
    for(in_iter = map_from.end() - 1; in_iter != map_from.begin() - 1; in_iter--){
      if((*iter).match(string(argv[(*in_iter)]))){

	map_from.erase(iter);
	if(map_from.size() < (*iter).arg_count())
	  throw exception_argument();

	vector<string> arg_vec;
	for(int i = 1; i < (*iter).arg_count(); i++){
	  arg_vec.push_back(string(argv[*(in_iter + i)]))
	  map_from.erase(in_iter + i);
	}
	opt_map[(*iter).letter] = pair(true, arg_vec);	  
      }
    }
  }
  
  if(map_from.size() > 0)
    throw exception_argument();
}

