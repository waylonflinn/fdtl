#include "gross_pitaevskii.h"

gross_pitaevskii::gross_pitaevskii(
	  int I,
	  int J,
	  pair<double, double> range_x,
	  pair<double, double> range_y,
	  const boundary& top,		// boundary objects for each boundary
	  const boundary& right,
	  const boundary& bottom,
	  const boundary& left,
	  double coeff_x,
	  double coeff_y,
	  double eigenvalue,
	  double parameter)
  : problem_basic(I, J, range_x, range_y, top, right, bottom, left),
    cx(coeff_x), cy(coeff_y), eig(eigenvalue), param(parameter),
    p1x(-1*cx*ssx*x.first*x.first), p2x(-1*cx*ssx*2*x.first*sx),
    p3x(-1*cx*ssx*ssx),
    p1y(-1*cy*ssx*y.first*y.first), p2y(-1*cy*ssx*2*sy*y.first),
    p3y(-1*cy*ssx*ssy),
    meig(ssx*eigenvalue),
    mparam(param)
        
{
  double norm_av = 1/((x.second-x.first)+(y.second-y.first));

  //vector<double> neg(gy-1, -norm_av);
  vector<double> pos(gy-1, norm_av);

  sol = vector< vector<double> >(((*this).gx - 1, pos);
  //sol.insert(sol.end(), gx/2, pos);
}
