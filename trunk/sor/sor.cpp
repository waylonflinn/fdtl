#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <string>
#include <cstdlib>
#include <cmath>
#include "argument.cpp"

#define PRECISION	4	// decimal digits to display
#define EPS		1.0e-5	// ratio of final residual to initial residual

using namespace std;

void init_solution(istream* p_input,
		   vector< vector<double> >* p_solution,
		   int height,
		   int width);

void write_solution(ostream* p_output,
		    vector< vector<double> >* p_solution,
		    int height,
		    int width);

int check_arg(argument& arg);
string usage();

int sor(double epsilon,
	vector< vector<double> >* p_solution,
	vector< vector<double> >* p_a,
	vector< vector<double> >* p_b,
	vector< vector<double> >* p_c,
	vector< vector<double> >* p_d,
	vector< vector<double> >* p_e,
	vector< vector<double> >* p_f);

double sor_norm(vector< vector<double> >* p_solution,
		vector< vector<double> >* p_a,
		vector< vector<double> >* p_b,
		vector< vector<double> >* p_c,
		vector< vector<double> >* p_d,
		vector< vector<double> >* p_e,
		vector< vector<double> >* p_f);

main(int argc, char* argv[])
{
  const double PI = 3.141592653589;
  const double ACCURACY = .002;


  /// declare

  int HEIGHT;
  int WIDTH;
  int status;			// the return status of this program
  argument arg(argc, argv);	/* an object for parsing command-line
				   arguments */
  vector< vector<double> >* p_solution;	// (pointer to) the solution to the PDE
  istream* p_input;		// (pointer to) the output stream
  ostream* p_output;		// (pointer to) the input stream

  // check for a help request
  if(arg.help_requested()){
      cout << usage();
      return 0;
  };

  /// initialize  
  HEIGHT = arg.points_r();
  WIDTH = arg.points_z();
  p_solution = new vector< vector<double> >;

  if(arg.input_file().size() > 0)
    p_input = new ifstream(arg.input_file().c_str());
  else
    p_input = &cin;

  if(arg.output_file().size() > 0)
    p_output = new ofstream(arg.output_file().c_str());
  else
    p_output = &cout;

  vector< vector<double> >& solution = (*p_solution);

  // read the boundary values from the specified file
  init_solution(p_input, p_solution, HEIGHT, WIDTH);

  /// process
  (*p_output) << setprecision(PRECISION);
  ostream& output = (*p_output);
  
  double norm_0;
  double norm;
  int iter;

  norm_0 = sor_norm(p_solution);
  iter = sor(EPS, p_solution,
	     p_a,
	     p_b,
	     p_c,
	     p_d,
	     p_e,
	     p_f);

  norm = sor_norm(p_solution,
		  p_a,
		  p_b,
		  p_c,
		  p_d,
		  p_e,
		  p_f);

  output << "# initial norm:\t" << norm_0 << endl;
  output << "# finial norm:\t" << norm << endl;
  output << "# ratio:\t" << norm/norm_0 << endl;
  output << "# iterations:\t" << iter << endl;

  // output
  write_solution(p_output, p_solution, HEIGHT, WIDTH);

  // cleanup
  if(p_input != &cin)
    delete p_input;
  if(p_output != &cout)
    delete p_output;
  delete p_solution;
}

double sor_norm(vector< vector<double> >* p_solution,
		vector< vector<double> >* p_a,
		vector< vector<double> >* p_b,
		vector< vector<double> >* p_c,
		vector< vector<double> >* p_d,
		vector< vector<double> >* p_e,
		vector< vector<double> >* p_f)
{
  double res;	// residual
  double norm;	// norm of the residual
  int HEIGHT, WIDTH;
  int i, j;
  vector< vector<double> >& solution = (*p_solution);
  vector< vector<double> >& a = (*p_a);
  vector< vector<double> >& b = (*p_b);
  vector< vector<double> >& c = (*p_c);
  vector< vector<double> >& d = (*p_d);
  vector< vector<double> >& e = (*p_e);
  vector< vector<double> >& f = (*p_f);

  HEIGHT = (solution.size() - 1);
  if(HEIGHT > 1) {
    WIDTH = (solution[0].size() - 1);
    if(WIDTH < 2)
      return 0;
  }
  else
    return 0;

  norm = 0;
  for(i = 1; i < HEIGHT; ++i){
    for(j = 1; j < WIDTH; ++j){
      res = (e[i][j]*solution[i][j]) -
	(a[i][j]*solution[i+1][j] + b[i][j]*solution[i-1][j] +
	 c[i][j]*solution[i][j+1] + d[i][j]*solution[i][j-1]) +
	f[i][j];
      norm += abs(res);
    }
  }
  
  return norm;
}

int sor(double epsilon,
	double rho,
	vector< vector<double> >* p_solution,
	vector< vector<double> >* p_a,
	vector< vector<double> >* p_b,
	vector< vector<double> >* p_c,
	vector< vector<double> >* p_d,
	vector< vector<double> >* p_e,
	vector< vector<double> >* p_f)
{
  const int MAX_COUNT = 10000;

  vector< vector<double> >& solution = (*p_solution);
  vector< vector<double> >& a = (*p_a);
  vector< vector<double> >& b = (*p_b);
  vector< vector<double> >& c = (*p_c);
  vector< vector<double> >& d = (*p_d);
  vector< vector<double> >& e = (*p_e);
  vector< vector<double> >& f = (*p_f);

  int HEIGHT;
  int WIDTH;
  int count;
  int i, j;
  double res;	// residual
  double norm;	// norm of the residual
  double norm_0;	// norm of the initial residual
  double omega;		// the overrelaxation parameter


  HEIGHT = (solution.size() - 1);
  if(HEIGHT > 1) {
    WIDTH = (solution[0].size() - 1);
    if(WIDTH < 2)
      return 0;
  }
  else
    return 0;

  norm = norm_0 = gs_norm(p_solution);
  count = 0;
  omega = 2.0/(1.0 + sqrt(1.0 - (rho*rho)));

  // relaxation algorithm (succesive overrelaxation)
  while((norm > (norm_0 * epsilon)) && (count < MAX_COUNT))
    {
      norm = 0;
      for(i = 1; i < HEIGHT; i++)
	{
	  for(j = 1; j < WIDTH; j++)
	    {
	      res = (e[i][j]*solution[i][j]) -
		(a[i][j]*solution[i+1][j] + b[i][j]*solution[i-1][j] +
		 c[i][j]*solution[i][j+1] + d[i][j]*solution[i][j-1]) +
		f[i][j];

	      //norm += abs(res); overestimates
	      
	      // set value
	      solution[i][j] = (solution[i][j] - omega*res/(-e[i][j]));
	    }
	}
      norm = sor_norm(p_solution,
		      p_a,
		      p_b,
		      p_c,
		      p_d,
		      p_e,
		      p_f);
      /*
      if((count % 100) == 0)
	cout << "# " << count << "th norm:\t" << norm << endl;
      */

      ++count;
    }
  // end of relaxation algorithm

  return count;
}

void init_solution(istream* p_input, vector< vector<double> >* p_solution, int height, int width)
{

  int HEIGHT = height;
  int WIDTH = width;
  const double PI = 3.141592653589;

  vector<double> boundary_value_vector(2*(HEIGHT)+2*(WIDTH));
  vector< vector<double> >& solution = *p_solution;
  istream& input = *p_input;
  //ostream_iterator<double> out(cout, " ");
  string line;
  string boundary_value;
  double average;
  int begin;
  int end;

  average = 0;
  end = 0;
  getline(input, line);

  // parse boundary_value_vector from input
  for(int i = 0; i < 2*(HEIGHT)+2*(WIDTH); i++)
    {
      double value;

      begin = end + 1;
      // find first space at or after begin
      end = line.find(' ', begin);

      boundary_value = line.substr(begin, (end-begin));

      value = strtod(boundary_value.c_str(), NULL);
      average += value;
      boundary_value_vector[i] = value;
    }

  average = average/(2*(HEIGHT)+2*WIDTH);

  // build matrix
  for(int j = 0; j < HEIGHT + 1; j++)
    {
      solution.push_back(vector<double>(WIDTH + 1, average));
    }

  // set boundary values
  // top (1)
  for(int i = 0; i < WIDTH + 1; i++)
    {
      solution[0][i] = boundary_value_vector[i];
    }
  // middle (J - 1)
  for(int j = 1; j < HEIGHT; j++)
    {
      solution[j][WIDTH] = boundary_value_vector[WIDTH + j];
      solution[j][0] = boundary_value_vector[((2*WIDTH)+(2*HEIGHT))-j];
    }
  // bottom (1)
  for(int i = 0; i < WIDTH + 1; i++)
    {
      solution[HEIGHT][WIDTH - i] 
	= boundary_value_vector[WIDTH+HEIGHT+i];
    }
}

void write_solution(ostream* p_output, vector< vector<double> >* p_solution, int height, int width)
{
  const int HEIGHT = height;
  const int WIDTH = width;

  ostream& output = (*p_output);
  vector< vector<double> >& solution = (*p_solution);

  ostream_iterator<double> output_iterator(output, " ");

  for(int j = 0; j < HEIGHT + 1; j++)
    {
      copy(solution[j].begin(), solution[j].end(), output_iterator);
      output << '\n';
    }
}

int check_arg(argument& arg)
{  return (arg.input_file().size() == 0); }

string usage()
{
  string usage("usage:\n");

  usage += "gs <options> <in_file>\n";
  usage += "\twhere (the optional) <options> is zero or more of:\n\n";
  usage += "\t-h\t\tprint this usage summary.\n";
  usage += "\t-o <out_file>\tuse <out_file> for output.\n";
  usage += "\t-a <num>\tset coefficient of first var (r) to <num>\n";
  usage += "\t-b <num>\tset coefficient of second var (z) to <num>\n";
  //usage += "\t-c <num>\tset coefficient of third var to <num>\n";
  usage += "\t-r <num>\tset maximum of first var (r) to <num>\n";
  usage += "\t-z <num>\tset maximum of second var (z) to <num>\n";
  usage += "\t-I <num>\tset number of grid points for first var to <num>\n";
  usage += "\t-J <num>\tset number of grid points for second var to <num>\n";
  usage += "\t-N <num>\tset grid to a square with <num> points on each side\n";
  usage += "\t-e <num>\tset initial eigenvalue to <num>\n\n";
  usage += "\tand <in_file> specifies a properly formatted text file ";
  usage += "containing\n\tboundary values.\n";
  usage += "\tif no input or output files are specified then stdin and ";
  usage += "stdout,\n\trespectively, are used instead.\n";

  return usage;
}
