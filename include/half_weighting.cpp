#include "half_weighting.h"

/* if N is the coarse length, fine must be 2N
 */
void half_weighting::operator()(const problem& fine, problem& coarse)
{

  int fI,fJ;
  int cI,cJ;
  int ci, cj;
  int fi, fj;
  cI = coarse.I();
  fI = fine.I();
  cJ = coarse.J();
  fJ = fine.I();

  for(fi=2,ci=1;ci < cI; ++ci, fi+=2){
    for(fj=2,cj=1; cj < cJ; ++cj, fj+=2){
      coarse.u(ci,cj) = 0.5*fine.at(fi,fj)+
	0.125*(fine.at(fi-1, fj) + fine.at(fi+1, fj) +
	      fine.at(fi, fj-1) + fine.at(fi, fj+1));
    }
  }
}

void half_weighting::operator()(const boundary& fine, boundary& coarse)
{  
  int ci,fi;
  int cI,fI;
  cI = coarse.size();
  fI = fine.size();
  if(fI != 2*cI)
    return;

  for(ci=0,fi=0;ci<cI;++ci,fi+=2)
    coarse[ci] = 0.5*(fine.at(fi)+fine.at(fi+1));

}
