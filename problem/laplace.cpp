#include "laplace.h"

laplace::laplace() {}

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

void laplace::grow(operator_prolong& op)
{
  laplace* temp = new laplace(*this);

  delete temp;
}

void laplace::shrink(operator_restrict& op)
{
  boundary top(((*this).tp).type(), ((*this).gy)/2, 0.0),
    left(((*this).lf).type(), ((*this).gx)/2, 0.0), bottom(top), right(left);

  op((*this).tp, top);
  op((*this).rt, right);
  op((*this).bt, bottom);
  op((*this).lf, left);
  laplace* temp = new laplace(((*this).gx)/2, ((*this).gy)/2, (*this).x,
			      (*this).y, top, right, bottom, left);

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

  delete temp;
}

laplace laplace::clone()
{ return laplace(*this); }
