#include "bilinear_interpolation.h"

/* if N is the coarse length, fine must be 2N
 */
void bilinear_interpolation::operator()(const problem& coarse, problem& fine)
{
  int fI,fJ;
  int cI,cJ;
  int ci, cj;
  int fi, fj;
  cI = coarse.I();
  fI = fine.I();
  cJ = coarse.J();
  fJ = fine.I();

 // existing points: odd rows, odd columns
  for(fi=2,ci=1;ci < cI; ++ci, fi+=2){
    for(fj=2,cj=1; cj < cJ; ++cj, fj+=2){
      fine.u(fi,fj) = coarse.at(ci,cj);
    }
  }
  /* even rows, odd columns, interpolate vertically
   */
  for(fi=1;fi < fI; fi+=2){
    for(fj=2; fj < fJ;fj+=2){
      fine.u(fi,fj) = 0.5*(fine.at(fi-1,fj)+fine.at(fi+1,fj));
    }
  }

  /* all even columns, interpolate horizontally
   */
  for(fj=1;fj < fJ; fj+=2){
    for(fi=1; fi < fI;++fi){
      fine.u(fi,fj) = 0.5*(fine.at(fi,fj-1)+fine.at(fi,fj+1));
    }
  }
}

void bilinear_interpolation::operator()(const boundary& coarse, boundary& fine)
{
  int ci,fi;
  int cI,fI;
  cI = coarse.size();
  fI = fine.size();
  if(fI != 2*cI)
    return;

  for(ci=0,fi=1;ci < cI-1; ++ci,fi+=2){
    fine[fi] = (0.75*coarse.at(ci))+(0.25*coarse.at(ci+1));
    fine[fi+1] = (0.25*coarse.at(ci))+(0.75*coarse.at(ci+1));
  }

  fine[0] = 2*fine[1]-fine[2];
  fine[fI-1] = 2*fine[fI-2]-fine[fI-3];
}
