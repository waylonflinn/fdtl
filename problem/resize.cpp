#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "next.cpp"


using std::cout;
using std::endl;
using std::vector;

next n(1);
double filler();
void bilinear_interp(vector<vector<double> >& coarse,
		  vector<vector<double> >& fine);
void half_weight(vector<vector<double> >& fine,
		 vector<vector<double> >& coarse);
void print(const vector<vector<double> >& V);
int main()
{
  int I,J;
  I = 10;
  J = 10;

  vector<double> interior(J+1, 0);
  generate(interior.begin()+1, interior.end()-1, filler);
  vector<vector<double> > V =
    vector<vector <double> >(I+1, interior);
  vector<vector<double> > fine =
    vector<vector <double> >(2*I+1, vector<double>(2*J+1, 0));

  for(int i=1; i < I;++i){
    V[0][i]=0;
    V[J][i]=0;
  }
  cout.precision(3);
  print(V);
  cout << endl;
  print(fine);
  bilinear_interp(V,fine);
  cout << endl;
  print(fine);
  cout << endl;

  vector<double> fine_int(2*J+1, 0);
  n = next(1);
  generate(fine_int.begin()+1, fine_int.end()-1, n);
  vector<vector<double> > fine_V =
    vector<vector <double> >(I*2+1, fine_int);
  vector<vector<double> > coarse =
    vector<vector <double> >(I+1, vector<double>(J+1, 0));
  for(int i=1; i < 2*I+1;++i){
    fine_V[0][i]=0;
    fine_V[2*J][i]=0;
  }
  half_weight(fine,coarse);
  print(fine_V);
  cout << endl;
  print(coarse);
  return 0;
}

void print(const vector<vector<double> >& V)
{
  int i,j;

  for(i = 0; i < V.size(); i++){
    for(j = 0; j < V[0].size(); j++){
      cout << V[i][j] << " ";
    }
    cout << endl;
  }
}
double filler()
{
  return 2*n();
}

/* if N+1 is the coarse dimension, fine must be 2N+1
 * uses random access iterator requirement (subscripting)
 */
void bilinear_interp(vector<vector<double> >& coarse,
		  vector<vector<double> >& fine)
{
  int fI,fJ;
  int cI,cJ;
  cI = coarse.size() - 1;
  fI = fine.size() - 1;
  if(fI == 0 || cI == 0)
    return;
  else{
    cJ = coarse[0].size() - 1;
    fJ = fine[0].size() - 1;
  }
  int ci, cj;
  int fi, fj;

  vector<vector<double> >::iterator it(coarse.begin());
  vector<vector<double> >::iterator it_fine(fine.begin());
  // existing points: odd rows, odd columns
  for(fi=2,ci=1;ci < cI; ++ci, fi+=2){
    for(fj=2,cj=1; cj < cJ; ++cj, fj+=2){
      it_fine[fi][fj] = it[ci][cj];
    }
  }
  /* even rows, odd columns, interpolate vertically
   */
  for(fi=1;fi < fI; fi+=2){
    for(fj=2; fj < fJ;fj+=2){
      it_fine[fi][fj] = 0.5*(it_fine[fi-1][fj]+it_fine[fi+1][fj]);
    }
  }
  /* all even columns, interpolate horizontally
   */

  for(fj=1;fj < fJ; fj+=2){
    for(fi=1; fi < fI;++fi){
      it_fine[fi][fj] = 0.5*(it_fine[fi][fj-1]+it_fine[fi][fj+1]);
    }
  }
}

void half_weight(vector<vector<double> >& fine,
		 vector<vector<double> >& coarse)
{

  int fI,fJ;
  int cI,cJ;
  cI = coarse.size();
  fI = fine.size();
  if(fI == 0 || cI == 0)
    return;
  else{
    cJ = coarse[0].size();
    fJ = fine[0].size();
  }
  int ci, cj;
  int fi, fj;

  vector<vector<double> >::iterator it_coarse(coarse.begin());
  vector<vector<double> >::iterator it_fine(fine.begin());
  for(fi=2,ci=1;ci < cI-1; ++ci, fi+=2){
    for(fj=2,cj=1; cj < cJ-1; ++cj, fj+=2){
      it_coarse[ci][cj] = 0.5*it_fine[fi][fj]+
	0.125*(it_fine[fi-1][fj] + it_fine[fi+1][fj] +
	      it_fine[fi][fj-1] + it_fine[fi][fj+1]);
    }
  }
}
