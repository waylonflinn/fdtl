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

// public constants
const int interface::DEF_I = 20;
const int interface::DEF_J = 20;
const pair<double, double> interface::DEF_X = pair<double, double>(0.0, 1.0);
const pair<double, double> interface::DEF_Y = pair<double, double>(-1.0, 1.0);

const argument interface::INPUT = 
 argument("file", "a properly formatted file to use for the input (or '-').");

const option interface::OPT_I =
 option('I', argument("n", "the number of points for "+interface::FIRST_VAR));

const option interface::OPT_J =
 option('J', argument("n", "the number of points for "+interface::SEC_VAR));

const option interface::OPT_X =
option('x', vector<argument>(interface::ARR_X, interface::ARR_X + 2));

const option interface::OPT_Y =
option('y', vector<argument>(interface::ARR_Y, interface::ARR_Y + 2));

const option interface::ARR_OPT[] =
  {interface::OPT_I, interface::OPT_J, interface::OPT_X, interface::OPT_Y};

int grid_opt(char let);
pair<double, double> range_opt(char let);

// constructors
interface::interface(string id, int argc, char* argv[]) :
  cl(id, vector<option>(ARR_OPT, ARR_OPT + 4), interface::INPUT),
  gx(interface::DEF_I), gy(interface::DEF_J), rx(interface::DEF_X),
  ry(interface::DEF_Y)
{
  try{
    cl.parse(argc, argv);
  }
  catch(invalid_argument e){
    cerr << e.what() << ", ";
    cerr << "usage: \n" << cl.usage() << endl;
    throw invalid_argument("malformed command line.");
  }


  gx = grid_opt('I');
  gy = grid_opt('J');

  rx = range_opt('x');
  ry = range_opt('y');

  // add output file and boundary code
}

interface::interface() :
  cl(interface::NAME, vector<option>(ARR_OPT, ARR_OPT + 4), interface::INPUT),
  gx(interface::DEF_I), gy(interface::DEF_J), rx(interface::DEF_X),
  ry(interface::DEF_Y)
{}


int interface::grid_opt(char let){
  int val;
  char* cerrstr[100];
  string errstr;
  bool error = false;

  if(cl[let].first){
   val = strtol(cl[let].second[0].c_str(), cerrstr, 10);
   error = (errstr.assign(*cerrstr).size() > 0);
   if(error || errno == EDOM || errno == ERANGE){
     cerr << "invalid argument to option '" << let << "': ('";
     cerr << cl[let].second[0] << "'); ";
     cerr << "usage: \n" << cl.usage() << endl;
     throw invalid_argument("malformed command line.");
   }
  }
  return val;

}
pair<double, double> interface::range_opt(char let){

  pair<double, double> val;
  char* cerrstr[100];
  string errstr;
  bool error = false;

  if(cl[let].first){
   val.first = strtod(cl[let].second[0].c_str(), cerrstr);
   error = (errstr.assign(*cerrstr).size() > 0);
   val.second = strtod(cl[let].second[1].c_str(), cerrstr);
   error |= (errstr.assign(*cerrstr).size() > 0);
   if(error || errno == EDOM || errno == ERANGE){
     cerr << "invalid arguments to option '"<< let << "': ('";
     cerr << cl[let].second[0] << "', '"<< cl[let].second[1] << "'); ";
     cerr << "usage: \n" << cl.usage() << endl;
     throw invalid_argument("malformed command line.");
   }
  }
  return val;
}
