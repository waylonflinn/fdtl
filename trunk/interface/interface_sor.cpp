#include "interface_sor.h"

double str_to_d(string str);

// constructors
interface_sor::interface_sor(string id, int argc, char* argv[]) :
       interface()
{

  vector<option> option_vec(option_set::ARR_OPT,
			    option_set::ARR_OPT + option_set::SIZE);
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
    rad = 1-(M_PI*M_PI/(2*gx*gy));	// default spectral radius (laplace)
    

  rx = make_range('x', interface::DEF_X);
  ry = make_range('y', interface::DEF_Y);

  make_bound();

  // add output file
}

interface_sor::interface_sor() :
       interface()
{}
