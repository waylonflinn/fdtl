#include <iostream>
#include <vector>
#include "command_line.cpp"

using std::cout;
using std::endl;
using std::vector;

int main(int argc, char* argv[])
{
  argument arg_file = argument("file", "a properly formatted file to use for the input");

  string first_var("the first variable (r)");
  string sec_var("the second variable (z)");

  // help option
  option opt_help('h', "print a usage summary");

  // I
  argument arg_I("n", "the number of points for " + first_var); 
  option opt_I('I', "set grid points for " + first_var, arg_I);

  // J
  argument arg_J("n", "the number of points for " + sec_var); 
  option opt_J('J', "set grid points for " + sec_var, arg_J);

  // output
  argument arg_out("output", "the file to use for output");
  option opt_out('o', "use a file for output");

  // first coefficient option
  argument arg_fcoef("a", "the coefficient to " + first_var);
  option opt_fcoef('a', "set the coefficient to " + first_var, arg_fcoef);

  // second coefficient option
  argument arg_scoef("b", "the coefficient to " + sec_var);
  option opt_scoef('b', "set the coefficient to " + sec_var, arg_scoef);

  // eigenvalue option
  argument arg_eig = argument("lam", "the eigenvalue");
  option opt_eig = option('e', "set the eigenvalue", arg_eig);

  // min and max r
  argument arg_min("r0", "the mininum for " + first_var);
  argument arg_max("r1", "the maximum for " + first_var);
  vector<argument> arg_vec(1, arg_min);
  arg_vec.push_back(arg_max);
  option opt_r('r', "set the min and max for" + first_var, arg_vec);
 
  // min and max z
  argument arg_minz("z0", "the mininum for " + sec_var);
  argument arg_maxz("z1", "the maximum for " + sec_var);
  vector<argument> arg_vecz(1, arg_minz);
  arg_vecz.push_back(arg_maxz);
  option opt_z('z', "set the min and max for" + sec_var, arg_vecz);
 
  // interaction parameter
  argument arg_k("k", "the interaction parameter");
  option opt_k('k', "set the interaction parameter", arg_k);

  vector<option> opt_vec = vector<option>(1, opt_help);
  opt_vec.push_back(opt_I);
  opt_vec.push_back(opt_J);
  opt_vec.push_back(opt_eig);
  opt_vec.push_back(opt_fcoef);
  opt_vec.push_back(opt_scoef);
  opt_vec.push_back(opt_r);
  opt_vec.push_back(opt_z);
  opt_vec.push_back(opt_k);

  command_line cl = command_line(opt_vec, arg_file);
 
  cout << "usage: \n" << cl.usage() << endl;

  return 0;
}
