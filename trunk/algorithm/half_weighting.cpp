#include "half_weighting.h"

/* if N+1 is the coarse dimension, fine must be 2N+1
 * uses random access iterator requirement (subscripting)
 */
void operator()(const problem& fine, problem& coarse)
{

  int fI,fJ;
  int cI,cJ;
  int ci, cj;
  int fi, fj;
  cI = coarse.I();
  fI = fine.I();
  cJ = coarse.J();
  fJ = fine.I();

  for(fi=2,ci=1;ci < cI-1; ++ci, fi+=2){
    for(fj=2,cj=1; cj < cJ-1; ++cj, fj+=2){
      coarse.u(ci,cj) = 0.5*fine.at(fi,fj)+
	0.125*(fine.at(fi-1, fj) + fine.at(fi+1, fj) +
	      fine.at(fi, fj-1) + fine.at(fi, fj+1));
    }
  }
}
