#include <iostream>
#include <vector>
#include "cl.cpp"

using std::cout;
using std::endl;
using std::vector;


int main(int argc, char* argv[])
{
  /*
  argument arg = argument("test-arg", "a test of argument");

  option empty = option();

  vector<option> opt_vec = vector<option>();

  opt_vec.push_back(opt);

  print(opt_vec[0]);

  */
  string token("  -p ");
  char letter = 'p';
  option opt = option('p', "a test of option");
  argument arg_eig = argument("double", "the eigenvalue");
  option opt_eig = option('e', "set the eigenvalue to %s", arg_eig);

  
  /*
  cout << option::PREFIX + 'p'  << endl;
  cout << "found: " << (token.find(option::PREFIX + 'p') != string::npos) << endl;
  cout << "found: " << opt.match(token) << endl;
  cout << "usage: " << endl;
  cout << opt_eig.usage() << endl;
  cout << arg_eig.usage() << endl;
  */

  return 0;
}
