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
    x0(x.first), y0(y.first), cx(coeff_x), cy(coeff_y), eig(eigenvalue),
    parm(parameter),
    p1x(-2*cx*ssx*x.first*x.first), p2x(-2*cx*ssx*2*x.first*sx),
    p3x(-2*cx*ssx*ssx),
    p1y(-2*cy*ssx*y.first*y.first), p2y(-2*cy*ssx*2*sy*y.first),
    p3y(-2*cy*ssx*ssy),
    meig(2*ssx*eigenvalue),
    mparm(-2*ssx*parm)
        
{
  double norm_av = 
    sqrt(1/((x.second-x.first)*(y.second-y.first)));

  //vector<double> neg(gy-1, -norm_av);
  vector<double> pos(gy-1, norm_av);

  sol = vector< vector<double> >((*this).gx - 1, pos);
  //sol.insert(sol.end(), gx/2, pos);
}

void gross_pitaevskii::grow(operator_prolong& op)
{
  gross_pitaevskii* temp = new gross_pitaevskii(*this);

  delete temp;
}

void gross_pitaevskii::shrink(operator_restrict& op)
{
  boundary top(((*this).tp).type(), ((*this).gy)/2, 0.0),
    left(((*this).lf).type(), ((*this).gx)/2, 0.0), bottom(top), right(left);

  op((*this).tp, top);
  op((*this).rt, right);
  op((*this).bt, bottom);
  op((*this).lf, left);
  gross_pitaevskii* temp =
    new gross_pitaevskii(((*this).gx)/2, ((*this).gy)/2, (*this).x,
			 (*this).y, top, right, bottom, left,
			 (*this).cx, (*this).cy, (*this).eig, (*this).parm );

  op(*this, *temp);
  (*this).sol = (*temp).sol;
  (*this).gx = (*temp).gx;
  (*this).gy = (*temp).gy;
  (*this).sx = (*temp).sx;
  (*this).sy = (*temp).sy;
  (*this).tp = (*temp).tp;
  (*this).rt = (*temp).rt;
  (*this).bt = (*temp).bt;
  (*this).lf = (*temp).lf;
  (*this).ssx = (*temp).ssx;
  (*this).ssy = (*temp).ssy;
  (*this).rss = (*temp).rss;
  (*this).ast = (*temp).ast;

  (*this).x0 = (*temp).x0;
  (*this).y0 = (*temp).y0;
  (*this).cx = (*temp).cx;
  (*this).cy = (*temp).cy;
  (*this).eig = (*temp).eig;
  (*this).parm = (*temp).parm;
  (*this).meig = (*temp).meig;
  (*this).mparm = (*temp).mparm;
  (*this).p1x = (*temp).p1x;
  (*this).p2x = (*temp).p2x;
  (*this).p3x = (*temp).p3x;
  (*this).p1y = (*temp).p1y;
  (*this).p2y = (*temp).p2y;
  (*this).p3y = (*temp).p3y;

  delete temp;
}

gross_pitaevskii gross_pitaevskii::clone()
{ return gross_pitaevskii(*this); }
