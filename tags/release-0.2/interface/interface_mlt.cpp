#include "interface_mlt.h"

const int interface_mlt::DEF_I = 40;
const int interface_mlt::DEF_J = 40;

const int interface_mlt::DEF_S = 5;

double str_to_d(string str);

// constructors
interface_mlt::interface_mlt(string id, int argc, char* argv[]) :
       interface(), gs(interface_mlt::DEF_S)
{

  vector<option> option_vec(option_set::ARR_OPT,
			    option_set::ARR_OPT + option_set::SIZE);

  option_vec.insert(option_vec.end(),
		    option_set_mlt::ARR_OPT,
		    option_set_mlt::ARR_OPT + option_set_mlt::SIZE);

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
    gx = make_grid('N', interface_mlt::DEF_I);
    gy = make_grid('N', interface_mlt::DEF_I);
  }
  else{
    gx = make_grid('I', interface_mlt::DEF_I);
    gy = make_grid('J', interface_mlt::DEF_J);
  }

  gs = make_grid('S', interface_mlt::DEF_S);

  rx = make_range('x', interface_mlt::DEF_X);
  ry = make_range('y', interface_mlt::DEF_Y);

  make_bound();

  // add output file code
}

interface_mlt::interface_mlt() :
       interface(), gs(interface_mlt::DEF_S)
{}
