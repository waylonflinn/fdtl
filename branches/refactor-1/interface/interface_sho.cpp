#include "interface_sho.h"

const double interface_sho::DEF_A = 1;

const double interface_sho::DEF_B = 1;

const double interface_sho::DEF_EIG = 0.5;

const pair<double,double> interface_sho::DEF_X =
pair<double,double>(-4, 4);

const pair<double,double> interface_sho::DEF_Y = interface_sho::DEF_X;

const option interface_sho::OPT_A =
 option('a', argument("w", "the coefficient to "+interface::FIRST_VAR));

const option interface_sho::OPT_B =
 option('b', argument("w", "the coefficient to "+interface::SEC_VAR));

const option interface_sho::OPT_EIG =
 option('e', argument("w", "the eigenvalue"));

const option interface_sho::ARR_OPT_SHO[] =
  {interface::OPT_I, interface::OPT_J, interface::OPT_X, interface::OPT_Y,
  interface_sho::OPT_A, interface_sho::OPT_B, interface_sho::OPT_EIG};

double str_to_d(string str);

// constructors
interface_sho::interface_sho(string id, int argc, char* argv[]) :
       interface(), cx(interface_sho::DEF_A),
       cy(interface_sho::DEF_B), eig(interface_sho::DEF_EIG) 
{
  cl = command_line(id, vector<option>(interface_sho::ARR_OPT_SHO,
				       interface_sho::ARR_OPT_SHO + 7),
		    interface::INPUT);

  try{
    cl.parse(argc, argv);
  }
  catch(invalid_argument e){
    cerr << e.what() << ", ";
    cerr << "usage: \n" << cl.usage() << endl;
    throw invalid_argument("malformed command line.");
  }


  gx = make_grid('I', interface::DEF_I);
  gy = make_grid('J', interface::DEF_J);

  rx = make_range('x', interface_sho::DEF_X);
  ry = make_range('y', interface_sho::DEF_Y);

  cx = (cl['a'].first) ? str_to_d(cl['a'].second[0]) : interface_sho::DEF_A;
  cy = (cl['b'].first) ? str_to_d(cl['b'].second[0]) : interface_sho::DEF_B;
  eig = (cl['e'].first) ? str_to_d(cl['e'].second[0]) : interface_sho::DEF_EIG;

  make_bound();

  // add output file and boundary code
}

interface_sho::interface_sho() :
       interface(), cx(interface_sho::DEF_A),
       cy(interface_sho::DEF_B), eig(interface_sho::DEF_EIG)
{}
