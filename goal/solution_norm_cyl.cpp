#include "solution_norm_cyl.h"


const double solution_norm_cyl::DEF_EPS = 1.0e-4;

solution_norm_cyl::solution_norm_cyl(const problem& prob, double epsilon) 
  : eps(epsilon)
{
}

solution_norm_cyl::solution_norm_cyl() : eps(solution_norm_cyl::DEF_EPS)
{
}

bool solution_norm_cyl::operator()(const problem& prob)
{
  double norm = solution_norm_cyl::norm(prob);

  return abs(1-norm) < eps;
}

double solution_norm_cyl::norm(const problem& prob)
{
  double line;	// integral along a grid line
  double norm;	// norm of solution, squared
  int I = prob.I();
  int J = prob.J();
  double sr, sz, r0;
  int i, j;

  r0 = prob.x0();
  sr = prob.dx();
  sz = prob.dy();
  norm = 0;

  // calc first (interior) line
  /* the (r0+(sr*i)) term is the 'r' term in the jacobian for cylindrical
   * coords
   */
  line = (23.0/12.0)*pow(prob.at(1,1),2);
  line += (7.0/12.0)*pow(prob.at(1,2),2);
  for(j = 3; j < J-2; ++j)
    line += pow(prob.at(1,j),2);
  line += (7.0/12.0)*pow(prob.at(1,J-2),2);
  line += (23.0/12.0)*pow(prob.at(1,J-1),2);
  line *= sz;
  norm += ((23.0/12.0)*line*(r0+sr));

  // second
  line = (23.0/12.0)*pow(prob.at(2,1),2);
  line += (7.0/12.0)*pow(prob.at(2,2),2);
  for(j = 3; j < J-2; ++j)
    line += pow(prob.at(2,j),2);
  line += (7.0/12.0)*pow(prob.at(2,J-2),2);
  line += (23.0/12.0)*pow(prob.at(2,J-1),2);
  line *= sz;
  norm += (7.0/12.0)*line*(r0+(sr*2));

  for(i = 3; i < I-2; ++i){
    line = (23.0/12.0)*pow(prob.at(i,1),2);
    line += (7.0/12.0)*pow(prob.at(i,2),2);
    for(j = 3; j < J-2; ++j){
      line += pow(prob.at(i,j),2);
    }
    line += (7.0/12.0)*pow(prob.at(i,J-2),2);
    line += (23.0/12.0)*pow(prob.at(i,J-1),2);
    line *= sz;
    norm += (line*(r0+(sr*i)));
  }

  // next to last
  line = (23.0/12.0)*pow(prob.at(I-2,1),2);
  line += (7.0/12.0)*pow(prob.at(I-2,2),2);
  for(j = 3; j < J-2; ++j)
    line += pow(prob.at(I-2,j),2);
  line += (7.0/12.0)*pow(prob.at(I-2,J-2),2);
  line += (23.0/12.0)*pow(prob.at(I-2,J-1),2);
  line *= sz;
  norm += (7.0/12.0)*line*(r0+(sr*(I-2)));

  // last
  line = (23.0/12.0)*pow(prob.at(I-1,1),2);
  line += (7.0/12.0)*pow(prob.at(I-1,2),2);
  for(j = 3; j < J-2; ++j)
    line += pow(prob.at(I-1,j),2);
  line += (7.0/12.0)*pow(prob.at(I-1,J-2),2);
  line += (23.0/12.0)*pow(prob.at(I-1,J-1),2);
  line *= sz;
  norm += (23.0/12.0)*line*(r0+(sr*(I-1)));

  norm *= sr;

  return 2*M_PI*norm;
}
