#include <iostream>
#include "interface.h"

int main(int argc, char* argv[])
{
  interface inter;
  try{
  inter = interface("test", argc, argv);
  }
  catch(invalid_argument e){
    cerr << e.what() << endl;
    return 1;
  }
  catch(...){
    cerr << "something bad happened!" << endl;
    return 1;
  }

  pair<double, double> x = inter.x();

  cout <<"x: " << x.first << ", " << x.second << endl;
  x = inter.y();
  cout <<"y: " << x.first << ", " << x.second << endl;
  cout << "I:" << inter.I() << endl;
  cout << "J:" << inter.J() << endl;

  boundary top = inter.top();

  if(top.type() == boundary::DIRICHLET)
    cout << "Dirichlet" << endl;
  else
    cout << "Neumann" << endl;

  for(int i = 0; i < inter.I(); ++i)
    cout << top.at(i) << " ";
  cout << endl;
  
  top = inter.bottom();

  if(top.type() == boundary::DIRICHLET)
    cout << "Dirichlet" << endl;
  else
    cout << "Neumann" << endl;

  for(int i = 0; i < inter.I(); ++i)
    cout << top.at(i) << " ";
  cout << endl;

}
