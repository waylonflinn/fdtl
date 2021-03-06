#include "gross_pitaevskii_cart.h"

gross_pitaevskii_cart::gross_pitaevskii_cart() {}

gross_pitaevskii_cart::gross_pitaevskii_cart(
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
    xm(x.first), ym(y.first), cx(coeff_x), cy(coeff_y), eig(eigenvalue),
    parm(parameter),
    p1x(-1*cx*ssx*x.first*x.first), p2x(-1*cx*ssx*2*x.first*sx),
    p3x(-1*cx*ssx*ssx),
    p1y(-1*cy*ssx*y.first*y.first), p2y(-1*cy*ssx*2*sy*y.first),
    p3y(-1*cy*ssx*ssy),
    meig(ssx*eigenvalue),
    mparm(-1*ssx*parm)
        
{
  double norm_av = 
    sqrt(1/((x.second-x.first)*(y.second-y.first)));

  //vector<double> neg(gy-1, -norm_av);
  vector<double> pos(gy-1, norm_av);

  sol = vector< vector<double> >((*this).gx - 1, pos);
  //sol.insert(sol.end(), gx/2, pos);
}

void gross_pitaevskii_cart::eigenvalue(double eig)
{
  (*this).eig = eig;
  (*this).meig = ssx*eig;
  
}

void gross_pitaevskii_cart::grow(operator_prolong& op)
{
  gross_pitaevskii_cart* temp = new gross_pitaevskii_cart(*this);

  delete temp;
}

void gross_pitaevskii_cart::shrink(operator_restrict& op)
{
  boundary top(((*this).tp).type(), ((*this).gy)/2, 0.0),
    left(((*this).lf).type(), ((*this).gx)/2, 0.0),
    bottom(((*this).bt).type(), ((*this).gy)/2, 0.0),
    right(((*this).rt).type(), ((*this).gx)/2, 0.0);

  op((*this).tp, top);
  op((*this).rt, right);
  op((*this).bt, bottom);
  op((*this).lf, left);
  gross_pitaevskii_cart* temp =
    new gross_pitaevskii_cart(((*this).gx)/2, ((*this).gy)/2, (*this).x,
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

  (*this).xm = (*temp).xm;
  (*this).ym = (*temp).ym;
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

gross_pitaevskii_cart gross_pitaevskii_cart::clone()
{ return gross_pitaevskii_cart(*this); }
