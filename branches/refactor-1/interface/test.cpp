#include <iostream>
#include "interface.h"

int main(int argc, char* argv[])
{
  interface inter;
  try{
  inter = interface("test", argc, argv);
  }
  catch(invalid_argument e){
  }
  catch(...){
    cerr << "something bad happened!" << endl;
  }

  pair<double, double> x = inter.x();
  int J = inter.J();

  cout << x.first << ", " << x.second << endl;
  cout << J << endl;

}
