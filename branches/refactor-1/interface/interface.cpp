#include "interface.h"

// protected constants
const string interface::NAME = "pde_prog";
const string interface::FIRST_VAR = "the first variable (x)";
const string interface::SEC_VAR = "the second variable (y)";

const argument interface::ARR_X[] =
 {argument("x0", "the mininum for " + interface::FIRST_VAR),
  argument("x1", "the maximum for " + interface::FIRST_VAR)};

const argument interface::ARR_Y[] =
 {argument("y0", "the mininum for " + interface::SEC_VAR),
  argument("y1", "the maximum for " + interface::SEC_VAR)};

const option interface::ARR_OPT[] =
  {interface::OPT_I, interface::OPT_J, interface::OPT_X, interface::OPT_Y};

// public constants
const int interface::DEF_I = 20;
const int interface::DEF_J = 20;
const pair<double, double> interface::DEF_X = pair<double, double>(0, 1);
const pair<double, double> interface::DEF_Y = pair<double, double>(-1, 1);

const argument interface::INPUT = 
 argument("file", "a properly formatted file to use for the input");
const option interface::OPT_I =
 option('I',
	argument("n", "the number of points for " + interface::FIRST_VAR)
	);
const option interface::OPT_J =
 option('J',
	argument("n", "the number of points for " + interface::SEC_VAR)
	);
const option interface::OPT_X =
option('x', vector<argument>(interface::ARR_X, interface::ARR_X + 2));

const option interface::OPT_Y =
option('y', vector<argument>(interface::ARR_Y, interface::ARR_Y + 2));

const command_line interface::CL =
command_line(interface::NAME,
	     vector<option>(ARR_OPT, ARR_OPT + 4), interface::INPUT);

// constructors
interface::interface(string id, int argc, char* argv[])
{
  try{
    CL.parse(argc, argv);
  }
  catch(invalid_argument e){
    cout << e.desc << ", ";
    cout << "usage: \n" << cl.usage() << endl;
    throw invalid_argument("malformed command line.");
  }
}
/*

int interface::I()
{ 
  if(!cl['I'].first)
    return interface::DEF_I;

  return cl['I'].second;
}

int interface::J()
{ 
  if(!cl['J'].first)
    return interface::DEF_I;

  return cl['J'].second;
}

int interface::x()
{ 
  if(!cl['x'].first)
    return interface::DEF_X;

  pair<double, double> min_max
}

int main(int argc, char* argv[])
{
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
*/
