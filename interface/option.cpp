#include "option.h"

const string option::PREFIX = "-";

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

bool option::match(const vector<string>::iterator begin,
		   const vector<string>::iterator end)
{
  bool match = ((*this).arg_count() + 1) == distance(begin, end);
  if(!match)
    return false;
  match &= ((*begin).find(option::PREFIX + (*this).let) != string::npos);

  return match;
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
	arg_desc += "\n\t\t" + (*iter).usage();
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
