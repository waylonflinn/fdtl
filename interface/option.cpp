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
  option(const char& letter, const string& description,
	 const vector<argument>& arg_vec);
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

const string option::ARG_NAME = "%np";	// noun phrase

option::option(const char& letter,
	       const string& description,
	       const argument& arg)
  : letter(letter), desc(description), arg_vec(1, arg)
{
}

option::option(const char& letter,
	       const string& description,
	       const vector<argument>& argument_vector)
  : letter(letter), desc(description), arg_vec(argument_vector)
{
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
  string arg_list;
  string arg_desc;

  if((*this).use.size() == 0){	// first call to function

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

    (*this).use = "\n\t" + option::PREFIX + (*this).letter + " " +
      arg_list + "\n\t" + (*this).desc + arg_desc;
  }

  return (*this).use;
}
