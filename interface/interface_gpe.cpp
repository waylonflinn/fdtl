#include "interface_gpe.h"


const double interface_gpe::DEF_A = 1;

const double interface_gpe::DEF_B = 1;

const pair<double,double> interface_gpe::DEF_X =
pair<double,double>(0, 2);

const pair<double,double> interface_gpe::DEF_Y = 
 pair<double, double>(-1, 1);

const double interface_gpe::DEF_PARM = 1;

double str_to_d(string str);

// constructors
interface_gpe::interface_gpe(string id, int argc, char* argv[]) :
       interface(), cx(interface_gpe::DEF_A),
       cy(interface_gpe::DEF_B), eig(0), parm(interface_gpe::DEF_PARM),
       eig_pres(false)
{

  vector<option> option_vec(option_set::ARR_OPT,
			    option_set::ARR_OPT + option_set::SIZE);
  option_vec.insert(option_vec.end(),
		    option_set_gpe::ARR_OPT,
		    option_set_gpe::ARR_OPT + option_set_gpe::SIZE);
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

  rx = make_range('x', interface_gpe::DEF_X);
  ry = make_range('y', interface_gpe::DEF_Y);

  cx = (cl['a'].first) ? str_to_d(cl['a'].second[0]) : interface_gpe::DEF_A;
  cy = (cl['b'].first) ? str_to_d(cl['b'].second[0]) : interface_gpe::DEF_B;
  parm = 
    (cl['k'].first) ? str_to_d(cl['k'].second[0]) : interface_gpe::DEF_PARM;

  if(cl['e'].first){
    eig = str_to_d(cl['e'].second[0]);
    eig_pres = true;
  }

  make_bound();

  // add output file code
}

interface_gpe::interface_gpe() :
       interface(), cx(interface_gpe::DEF_A),
       cy(interface_gpe::DEF_B), eig(0), parm(interface_gpe::DEF_PARM),
       eig_pres(false)
{}
