#include "interface.h"

/// public constants
// defaults
const int interface::DEF_I = 20;
const int interface::DEF_J = 20;
const pair<double, double> interface::DEF_X = pair<double, double>(0.0, 1.0);
const pair<double, double> interface::DEF_Y = pair<double, double>(0.0, 1.0);

/// protected constants
double str_to_d(string str);

// constructors
interface::interface(string id, int argc, char* argv[]) :
	cl(id,
		vector<option>(option_set::ARR_OPT,
				option_set::ARR_OPT + option_set::SIZE),
		option_set::INPUT),
	gx(interface::DEF_I), gy(interface::DEF_J), rx(interface::DEF_X),
	ry(interface::DEF_Y), hdr(false)
{
	try
	{	cl.parse(argc, argv);}
	catch(invalid_argument e)
	{
		cerr << e.what() << ", ";
		cerr << "usage: \n" << cl.usage() << endl;
		throw invalid_argument("malformed command line.");
	}

	if(cl['h'].first)
	{
		cout << "usage: \n" << cl.usage() << endl;
		throw help_exception();
	}
	if(cl['d'].first)
	hdr = true;

	if(cl['N'].first)
	{
		gx = make_grid('N', interface::DEF_I);
		gy = make_grid('N', interface::DEF_I);
	}
	else
	{
		gx = make_grid('I', interface::DEF_I);
		gy = make_grid('J', interface::DEF_J);
	}

	rx = make_range('x', interface::DEF_X);
	ry = make_range('y', interface::DEF_Y);

	make_bound();

	// add output file code
}

interface::interface() :
	cl(option_set::NAME,
		vector<option>(option_set::ARR_OPT,
		option_set::ARR_OPT + option_set::SIZE),
	option_set::INPUT),
	gx(interface::DEF_I), gy(interface::DEF_J), rx(interface::DEF_X),
	ry(interface::DEF_Y), hdr(false)
{}

int interface::make_grid(char let, int def)
{
	int val;
	char*cerrstr [100];
	string errstr;
	bool error = false;

	if (cl[let].first)
	{
		val = strtol(cl[let].second[0].c_str(), cerrstr, 10);
		error = (errstr.assign(*cerrstr).size() > 0);
		if (error || errno == EDOM || errno == ERANGE)
		{
			cerr << "invalid argument to option '" << let << "': ('";
			cerr << cl[let].second[0] << "'); ";
			cerr << "usage: \n" << cl.usage() << endl;
			throw invalid_argument("malformed command line.");
		}
	}
	else val = def;
	
	return val;

}

pair<double, double> interface::make_range(char let, pair<double, double> def)
{
	pair<double,double> val;
	char* cerrstr[100];
	string errstr;
	bool error = false;

	if (cl[let].first)
	{
		val.first = strtod(cl[let].second[0].c_str(), cerrstr);
		error = (errstr.assign(*cerrstr).size() > 0);
		val.second = strtod(cl[let].second[1].c_str(), cerrstr);
		error |= (errstr.assign(*cerrstr).size() > 0);
		if (error || errno == EDOM || errno == ERANGE)
		{
			cerr << "invalid arguments to option '"<< let << "': ('";
			cerr << cl[let].second[0] << "', '"<< cl[let].second[1] << "'); ";
			cerr << "usage: \n" << cl.usage() << endl;
			throw invalid_argument("malformed command line.");
		}
	} else	val = def;
	
	return val;
}

// call after grid and range functions
void interface::make_bound()
{

	int i, j;
	int type;
	int begin, end;
	istream* p_in;
	if (cl.arg_val() == "-") p_in = &cin;
	else	p_in = new ifstream(cl.arg_val().c_str());

	istream& in = *p_in;
	string line;
	vector<double> bound(2*gx+2*gy, 0);
	vector<double>::iterator iter = bound.begin();
	vector<double>::iterator arr_it[5];
	int arr_type[4] = {boundary::DIRICHLET, boundary::DIRICHLET,
		boundary::DIRICHLET, boundary::DIRICHLET};

	end = 0;
	arr_it[0] = bound.begin();
	for (i = 0; i < 4; ++i)
	{
		getline(in, line);
		if (tolower(line.at(0)) == 'd')
		{
			getline(in, line);
		}
		else if (tolower(line.at(0)) == 'n')
		{
			arr_type[i] = boundary::NEUMANN;
			getline(in, line);
		}
		else if (isdigit(line.at(0)))
		{
		}
		else throw invalid_argument("malformed input file.");
		
		if ((i % 2) == 0)
		{ // top or bottom
			if (line.size() == 1 && isdigit(line.at(0)))
			{
				double val = str_to_d(line.substr(0, 1));
				for (j = 0; j < gy; ++j)
				{
					(*iter) = val;
					iter++;
				}
			}
			else
			{
				for (j = 0; j < gy; ++j)
				{
					begin = end + 1;
					end = line.find(' ', begin);
					(*iter) = str_to_d(line.substr(begin, (end-begin)));
					iter++;
				}
			}
		}
		else
		{ // left or right
			if (line.size() == 1 && isdigit(line.at(0)))
			{
				double val = str_to_d(line.substr(0, 1));
				for (j = 0; j < gx; ++j)
				{
					(*iter) = val;
					iter++;
				}
			}
			else
			{
				for (j = 0; j < gx; ++j)
				{
					begin = end + 1;
					end = line.find(' ', begin);
					(*iter) = str_to_d(line.substr(begin, (end-begin)));
					iter++;
				}
			}
		}
		arr_it[i+1] = vector<double>::iterator(iter);
	}
	tp = boundary(arr_type[0], arr_it[0], arr_it[1]);
	rt = boundary(arr_type[1], arr_it[1], arr_it[2]);
	bt = boundary(arr_type[2], arr_it[2], arr_it[3]);
	lf = boundary(arr_type[3], arr_it[3], arr_it[4]);

	if (!(cl.arg_val() == "-"))
	delete p_in;
}

/* a modern version of strtod.
 * takes a string (basic_string<char>) and interprets it as a number which may
 * be represented by the type double, then returns that double.
 * throws 'invalid_argument' if the string's contents are not representable
 * by the type double.
 */
double str_to_d(string str)
{

	double val;
	char* cerrstr[100];
	string errstr;
	bool error = false;

	val = strtod(str.c_str(), cerrstr);
	error |= (errstr.assign(*cerrstr).size() > 0);
	if (error || errno == ERANGE)
	{
		throw invalid_argument("string does not contain a value representable by type double.");
	}

	return val;
}
