#include <string>
#include <utility>
#include <vector>
#include <map>
#include "option.cpp"

using std::vector;
using std::string;
using std::pair;
using std::map;

class cl {
public:
  // constants

  // constructors
  cl(const vector<option>& option_vector, const argument& argument);
  cl();

  // methods
  const pair<bool, vector<string> >& operator[](const char& letter)
  { return opt_map[letter]; }


  const pair<bool, string>& arg_val() const 
  { return arg_pair; }

  const string& usage();

private:
  string prog_name;
  vector<option> opt_vec;
  argument arg;
  map<char, pair<bool, vector<string> > > opt_map;
  pair<bool, string> arg_pair;

  string use;
};

cl::cl(const vector<option>& option_vector, const argument& argument)
  : opt_vec(option_vector), arg(argument), use()
{
}

cl::cl() : opt_vec(), arg()
{
}

const string& cl::usage()
{
  if((*this).use.size() == 0){
    (*this).use = prog_name + " <options> " + arg.name();

    (*this).use += "\n\twhere <options> is zero or more of:\n";

    vector<option>::iterator iter = opt_vec.begin();
    for(iter = opt_vec.begin(); iter != opt_vec.end(); iter++){
      (*this).use += "\n\t" + (*iter).usage();
    }

    (*this).use += "\n\n\tand " + arg.name() + " specifies " +
      arg.description();
  }

  return (*this).use;
}
