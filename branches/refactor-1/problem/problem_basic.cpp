#include "problem_basic.h"

problem_basic::problem_basic(int I,
		 int J,
		 double range_x,
		 double range_y,
		 const boundary& top,
		 const boundary& right,
		 const boundary& bottom,
		 const boundary& left) 
  : gx(I), gy(J), sx(range_x/I), sy(range_y/J), tp(top), rt(right), bt(bottom),
    lf(left)
{
  int i;
  double average;

  average = 0;
  if(tp.type() == boundary::DIRICHLET)
  for(i = 0; i < (*this).gx; i++){
    average += (*this).tp.at(i);
  }
  if(bt.type() == boundary::DIRICHLET)
  for(i = 0; i < (*this).gx; i++){
    average += (*this).bt.at(i);
  }
  if(rt.type() == boundary::DIRICHLET)
  for(i = 0; i < (*this).gy; i++){
    average += (*this).rt.at(i);
  }
  if(lf.type() == boundary::DIRICHLET)
  for(i = 0; i < (*this).gy; i++){
    average += (*this).lf.at(i);
  }

  average = average / ((2*(*this).gx)+(2*(*this).gy));

  sol = vector< vector<double> >((*this).gx - 1,
				 vector<double>((*this).gy - 1, average));
}

double& problem_basic::u(int i, int j)
{ return sol[i-1][j-1]; }

double problem_basic::at(int i, int j) const
{
  if( j >= gy  && i < gx ){			// top
    if(tp.type() == boundary::DIRICHLET)
      return tp.at(i);
    else
      return at(i,j-1) + tp.at(i)*sx;
  }
  else if(i < 1){				// left
    if(lf.type() == boundary::DIRICHLET)
      return lf.at(j);
    else
      return at(i+1,j) - lf.at(j)*sx;
  }
  else if(j < 1){				// bottom
    if(bt.type() == boundary::DIRICHLET)
      return bt.at(gx-i);
    else
      return at(i,j+1) - bt.at(gx-i)*sx;
  }
  else if(i >= gx){				// right
    if(rt.type() == boundary::DIRICHLET)
      return rt.at(gy-j);
    else
      return at(i-1,j) + rt.at(gy-j)*sx;
  }
  else						// interior
    return sol[i-1][j-1];
}