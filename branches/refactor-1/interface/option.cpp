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
  
  // constructors
  option(const char& letter, const string& description,
	 const vector<argument>& arg_vec);
  option(const char& letter, const string& description, const argument& arg);
  option(const char& letter, const string& description);
  option(const char& letter, const vector<argument>& arg_vec);
  option(const char& letter, const argument& arg);
  option();

  // methods
  char letter() const { return let; }
  int arg_count() const { return arg_vec.size(); }
  bool match(const string& token);
  const string& usage();

private:
  char let;
  string desc;
  vector<argument> arg_vec;
  string use;
};

const string option::PREFIX = "-";

option::option(const char& letter,
	       const string& description,
	       const argument& arg)
  : let(letter), desc(description), arg_vec(1, arg)
{
}

option::option(const char& letter,
	       const string& description,
	       const vector<argument>& argument_vector)
  : let(letter), desc(description), arg_vec(argument_vector)
{
}

option::option(const char& letter,
	       const string& description)
  : let(letter), desc(description), arg_vec()
{
}

option::option(const char& letter,
	       const vector<argument>& argument_vector)
  : let(letter), arg_vec(argument_vector)
{
}

option::option(const char& letter,
	       const argument& arg)
  : let(letter), arg_vec(1, arg)
{
}

option::option()
  : let(0), desc(), arg_vec()
{
}

bool option::match(const string& token)
{
  return (token.find(option::PREFIX + (*this).let) != string::npos);
}

const string& option::usage()
{
  string arg_list;
  string arg_desc;
  string opt_desc;

  if((*this).use.size() == 0){	// first call to function

    if((*this).desc.size() > 0)
      opt_desc = "\t" + (*this).desc;

    vector<argument>::iterator iter = arg_vec.begin();
    vector<argument>::iterator end = arg_vec.end();
    for( ; iter != end; iter++){
      arg_list += "<" + (*iter).name() + "> ";

      if(iter == arg_vec.begin())
	arg_desc += "\n\t\twhere " + (*iter).usage();
      else if(iter == (arg_vec.end() - 1))
	arg_desc += "\n\t\tand " + (*iter).usage();
      else
	arg_desc += ",\n\t\t" + (*iter).usage();
    }

    (*this).use = "\n\t" + option::PREFIX + (*this).let + " " +
      arg_list + opt_desc + arg_desc;
  }

  return (*this).use;
}
