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
  option opt_I('I',  argument("n", "the number of points for " + first_var));

  // J
  option opt_J('J', argument("n", "the number of points for " + sec_var));

  // output
  option opt_out('o', argument("output", "the file to use for output"));

  // first coefficient option
  option opt_fcoef('a',  argument("a", "the coefficient to " + first_var));

  // second coefficient option
  option opt_scoef('b', argument("b", "the coefficient to " + sec_var));

  // eigenvalue option
  option opt_eig = option('e', argument("lam", "the eigenvalue"));

  // min and max r
  argument r_arr[2] = {argument("r0", "the mininum for " + first_var),
			 argument("r1", "the maximum for " + first_var)};
  option opt_r('r', vector<argument>(r_arr, r_arr + 2));
 
  // min and max z
  argument z_arr[2] = {argument("z0", "the mininum for " + sec_var),
			 argument("z1", "the maximum for " + sec_var)};
  option opt_z('z', vector<argument>(z_arr, z_arr + 2));

  // interaction parameter
  option opt_k('k',  argument("k", "the interaction parameter"));

  option opt_arr[] = {opt_I, opt_J, opt_out, opt_eig, opt_fcoef, opt_scoef,
		      opt_r, opt_z, opt_k};

  command_line cl =
    command_line("interface", vector<option>(opt_arr, opt_arr + 9), arg_file);

  try{
    cl.parse(argc, argv);
  }
  catch(exception_argument e){
    cout << e.desc << ", ";
    cout << "usage: \n" << cl.usage() << endl;
    return 1;
  }

  if(cl['h'].first)
    cout << "usage: \n" << cl.usage() << endl;
  if(cl['r'].first)
    cout << "r: " << cl['r'].second[0] << ", " << cl['r'].second[1] << endl;
  if(cl['z'].first)
    cout << "z: " << cl['z'].second[0] << ", " << cl['z'].second[1] << endl;
  if(cl['I'].first)
    cout << "I: " << cl['I'].second[0] << endl;
  if(cl['J'].first)
    cout << "J: " << cl['J'].second[0] << endl;
  if(cl['e'].first)
    cout << "e: " << cl['e'].second[0]  << endl;
  if(cl['k'].first)
    cout << "k: " << cl['k'].second[0]  << endl;
  

  return 0;
}
