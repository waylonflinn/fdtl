#include "interface_eig.h"


const int interface_eig::DEF_I = 40;
const int interface_eig::DEF_J = 40;

const double interface_eig::DEF_L = 1.0;

const pair<double,double> interface_eig::DEF_X =
pair<double,double>(0, 4);

const pair<double,double> interface_eig::DEF_Y = 
 pair<double, double>(-4, 4);

const double interface_eig::DEF_NUM = 10;

const double interface_eig::DEF_SCAT = 0.00433;	// rubidium

const int interface_eig::DEF_S = 20;

double str_to_d(string str);

// constructors
interface_eig::interface_eig(string id, int argc, char* argv[]) :
       interface(), lam(interface_eig::DEF_L),
       num(interface_eig::DEF_NUM), eig(0), scat(interface_eig::DEF_SCAT),
       eig_pres(false), gs(interface_eig::DEF_S)
{

  vector<option> option_vec(option_set::ARR_OPT,
			    option_set::ARR_OPT + option_set::SIZE);

  option_vec.insert(option_vec.end(),
		    option_set_mlt::ARR_OPT,
		    option_set_mlt::ARR_OPT + option_set_mlt::SIZE);

  option_vec.insert(option_vec.end(),
		    option_set_eig::ARR_OPT,
		    option_set_eig::ARR_OPT + option_set_eig::SIZE);

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
    gx = make_grid('N', interface_eig::DEF_I);
    gy = make_grid('N', interface_eig::DEF_I);
  }
  else{
    gx = make_grid('I', interface_eig::DEF_I);
    gy = make_grid('J', interface_eig::DEF_J);
  }

  gs = make_grid('S', interface_eig::DEF_S);

  rx = make_range('x', interface_eig::DEF_X);
  ry = make_range('y', interface_eig::DEF_Y);

  lam = (cl['l'].first) ? str_to_d(cl['l'].second[0]) : interface_eig::DEF_L;
  num = 
    (cl['n'].first) ? str_to_d(cl['n'].second[0]) : interface_eig::DEF_NUM;
  scat =
    (cl['a'].first) ? str_to_d(cl['a'].second[0]) : interface_eig::DEF_SCAT;

  if(cl['e'].first){
    eig = str_to_d(cl['e'].second[0]);
    eig_pres = true;
  }

  make_bound();

  // add output file code
}

interface_eig::interface_eig() :
       interface(), lam(interface_eig::DEF_L),
       num(interface_eig::DEF_NUM), eig(0), scat(interface_eig::DEF_SCAT),
       eig_pres(false), gs(interface_eig::DEF_S)
{}
