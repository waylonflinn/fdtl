#include "boundary.h"

boundary::boundary(int type,
		   vector<double>::iterator start,
		   vector<double>::iterator end) : tp(type), val(start, end)
{}

boundary::boundary() : tp(boundary::DIRICHLET)
{}

double boundary::at(int i) const
{ 
  if(i < 1)
    return val[0];
  else if(i >= val.size())
    return val.back();
  else
    return val[i];
}

double& boundary::operator[](int i) 
{ return val[i]; }
