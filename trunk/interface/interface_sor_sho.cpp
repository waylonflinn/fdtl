#include "interface_sor_sho.h"


const double interface_sor_sho::DEF_A = 1;

const double interface_sor_sho::DEF_B = 1;

const double interface_sor_sho::DEF_EIG = 0.5;

const pair<double,double> interface_sor_sho::DEF_X =
pair<double,double>(-4, 4);

const pair<double,double> interface_sor_sho::DEF_Y = interface_sor_sho::DEF_X;

double str_to_d(string str);

// constructors
interface_sor_sho::interface_sor_sho(string id, int argc, char* argv[]) :
       interface(), cx(interface_sor_sho::DEF_A),
       cy(interface_sor_sho::DEF_B), eig(interface_sor_sho::DEF_EIG)
{

  vector<option> option_vec(option_set::ARR_OPT,
			    option_set::ARR_OPT + option_set::SIZE);
  option_vec.insert(option_vec.end(),
		    option_set_sho::ARR_OPT,
		    option_set_sho::ARR_OPT + option_set_sho::SIZE);
  option_vec.insert(option_vec.end(),
		    option_set_sor::ARR_OPT,
		    option_set_sor::ARR_OPT + option_set_sor::SIZE);
  cl = command_line(id, option_vec, option_set::INPUT);

  try{
    cl.parse(argc, argv);
  }
  catch(invalid_argument e){
    cerr << e.what() << ", ";
    cerr << "usage: \n" << cl.usage() << endl;
    throw invalid_argument("malformed command line.");
  }

  if(cl['h'].first){
    cout << "usage: \n" << cl.usage() << endl;
    throw help_exception();
  }
  if(cl['d'].first)
    hdr = true;

  if(cl['N'].first){
    gx = make_grid('N', interface::DEF_I);
    gy = make_grid('N', interface::DEF_I);
  }
  else{
    gx = make_grid('I', interface::DEF_I);
    gy = make_grid('J', interface::DEF_J);
  }
  if(cl['r'].first)
    rad = str_to_d(cl['r'].second[0]);
  else
    rad = 1-(2.6*M_PI*M_PI/(gx*gy));	// default spectral radius (laplace)


  rx = make_range('x', interface_sor_sho::DEF_X);
  ry = make_range('y', interface_sor_sho::DEF_Y);

  cx = (cl['a'].first) ? str_to_d(cl['a'].second[0]) : interface_sor_sho::DEF_A;
  cy = (cl['b'].first) ? str_to_d(cl['b'].second[0]) : interface_sor_sho::DEF_B;
  eig = (cl['e'].first) ? str_to_d(cl['e'].second[0]) : interface_sor_sho::DEF_EIG;

  make_bound();

  // add output file and boundary code
}

interface_sor_sho::interface_sor_sho() :
       interface(), cx(interface_sor_sho::DEF_A),
       cy(interface_sor_sho::DEF_B), eig(interface_sor_sho::DEF_EIG)
{}
