#include "command_line.h"

command_line::command_line(string name,
			   const vector<option>& option_vector,
			   const argument& argument)
  : opt_vec(option_vector), arg(argument), prog_name(name),
    help('h', "print a usage summary")
{
}

command_line::command_line() : opt_vec(), arg(), help('h', "print a usage summary")
{
}

const string& command_line::usage()
{
  if((*this).use.size() == 0){
    (*this).use = prog_name + " <options> " + "<" + arg.name() + ">";

    (*this).use += "\n\twhere <options> is zero or more of:\n";

    (*this).use += (*this).help.usage();

    vector<option>::iterator iter;
    for(iter = opt_vec.begin(); iter != opt_vec.end(); iter++){
      (*this).use += (*iter).usage();
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

  vector<option>::iterator opt_iter = (*this).opt_vec.begin();
  vector<option>::iterator opt_end_iter = (*this).opt_vec.end();
  for( ;opt_iter != opt_end_iter; ++opt_iter)
    (*this).opt_map[(*opt_iter).letter()] =
	  pair<bool, vector<string> >(false, vector<string>());
	
  if(argc == 0)
    return;
  if(argc == 1)
    throw exception_argument("no arguments");

  vector<string> user_arg(argv + 1, argv + argc);// user supplied arguments
  vector<string>::iterator iter = (user_arg.end() - 1);
  for(;iter != (user_arg.begin() - 1); --iter){
    if((*this).help.match(iter, iter + 1)){
      (*this).opt_map[help.letter()] =
	pair<bool, vector<string> >(true, vector<string>());
      return;
    }
  }
  
  
  (*this).arg_string = user_arg.back();
  user_arg.pop_back();
  bool found;
  iter = (user_arg.end() - 1);
  vector<string>::iterator end_iter = user_arg.end();
  for(;iter != (user_arg.begin() - 1); --iter){
    found = false;
    opt_iter = (*this).opt_vec.begin();
    opt_end_iter = (*this).opt_vec.end();
    for( ; !found && (opt_iter != opt_end_iter); ++opt_iter){
      if((*opt_iter).match(iter, end_iter)) {
	found = true;
	(*this).opt_map[(*opt_iter).letter()] =
	  pair<bool, vector<string> >(true, vector<string>(iter + 1, end_iter));
	end_iter = iter;
      }
    }
  }
  if(end_iter != user_arg.begin())
    throw exception_argument("unknown arguments");
}
