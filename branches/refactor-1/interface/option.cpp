#include <string>
#include <vector>
#include "argument.cpp"

using std::vector;
using std::string;

class option
{
public:
  // constants
  const static string PREFIX;	// identifies an option
  const static string ARG_NAME;	// placeholder for an argument name
  
  // constructors
  option(const char& letter, const string& description, const argument& arg);
  option(const char& letter, const string& description);
  option();

  // methods
  bool match(const string& token);
  const string& usage();

private:
  char letter;
  string desc;
  vector<argument> arg_vec;
  string use;
};

const string option::PREFIX = "-";

const string option::ARG_NAME = "%s";

option::option(const char& letter,
	       const string& description,
	       const argument& arg)
  : letter(letter), desc(description), arg_vec(1, arg)
{
  // interpret description
  string::size_type loc = desc.find(option::ARG_NAME);
  string::size_type len = option::ARG_NAME.size();
  string arg_name = "<" + arg_vec[0].name() + ">";

  (*this).desc.replace(loc, len, arg_name);
}

option::option(const char& letter,
	       const string& description)
  : letter(letter), desc(description), arg_vec()
{
}

option::option()
  : letter(0), desc(), arg_vec()
{
}

bool option::match(const string& token)
{
  return (token.find(option::PREFIX + (*this).letter) != string::npos);
}

const string& option::usage()
{

  if((*this).use.size() == 0){
    string arg_name = (arg_vec.size() == 0) ? "" : "<" + arg_vec[0].name() + ">";
    (*this).use = option::PREFIX + (*this).letter + " " + arg_name + "\t" + 
      (*this).desc;
  }

  return (*this).use;
}
