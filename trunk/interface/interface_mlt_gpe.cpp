#include "interface_mlt_gpe.h"


const int interface_mlt_gpe::DEF_I = 40;
const int interface_mlt_gpe::DEF_J = 40;

const double interface_mlt_gpe::DEF_A = 0.5;

const double interface_mlt_gpe::DEF_B = 0.5;

const pair<double,double> interface_mlt_gpe::DEF_X =
pair<double,double>(0, 4);

const pair<double,double> interface_mlt_gpe::DEF_Y = 
 pair<double, double>(-4, 4);

const double interface_mlt_gpe::DEF_PARM = 1;

const int interface_mlt_gpe::DEF_S = 10;

double str_to_d(string str);

// constructors
interface_mlt_gpe::interface_mlt_gpe(string id, int argc, char* argv[]) :
       interface(), cx(interface_mlt_gpe::DEF_A),
       cy(interface_mlt_gpe::DEF_B), eig(0), parm(interface_mlt_gpe::DEF_PARM),
       eig_pres(false), gs(interface_mlt_gpe::DEF_S)
{

  vector<option> option_vec(option_set::ARR_OPT,
			    option_set::ARR_OPT + option_set::SIZE);

  option_vec.insert(option_vec.end(),
		    option_set_mlt::ARR_OPT,
		    option_set_mlt::ARR_OPT + option_set_mlt::SIZE);

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
    gx = make_grid('N', interface_mlt_gpe::DEF_I);
    gy = make_grid('N', interface_mlt_gpe::DEF_I);
  }
  else{
    gx = make_grid('I', interface_mlt_gpe::DEF_I);
    gy = make_grid('J', interface_mlt_gpe::DEF_J);
  }

  gs = make_grid('S', interface_mlt_gpe::DEF_S);

  rx = make_range('x', interface_mlt_gpe::DEF_X);
  ry = make_range('y', interface_mlt_gpe::DEF_Y);

  cx = (cl['a'].first) ? str_to_d(cl['a'].second[0]) : interface_mlt_gpe::DEF_A;
  cy = (cl['b'].first) ? str_to_d(cl['b'].second[0]) : interface_mlt_gpe::DEF_B;
  parm = 
    (cl['k'].first) ? str_to_d(cl['k'].second[0]) : interface_mlt_gpe::DEF_PARM;

  if(cl['e'].first){
    eig = str_to_d(cl['e'].second[0]);
    eig_pres = true;
  }

  make_bound();

  // add output file code
}

interface_mlt_gpe::interface_mlt_gpe() :
       interface(), cx(interface_mlt_gpe::DEF_A),
       cy(interface_mlt_gpe::DEF_B), eig(0), parm(interface_mlt_gpe::DEF_PARM),
       eig_pres(false), gs(interface_mlt_gpe::DEF_S)
{}
