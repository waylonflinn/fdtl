#include "laplace.h"

laplace::laplace(int I,
		 int J,
		 pair<double, double> range_x,
		 pair<double, double> range_y,
		 const boundary& top,
		 const boundary& right,
		 const boundary& bottom,
		 const boundary& left) 
  : problem_basic(I, J, range_x, range_y, top, right, bottom, left)
    
{
}
