#include "bilinear_interpolation.h"

/* if N+1 is the coarse dimension, fine must be 2N+1
 * uses random access iterator requirement (subscripting)
 */
void operator()(const problem& coarse, problem& fine)
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
