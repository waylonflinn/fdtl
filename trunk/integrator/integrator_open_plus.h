/* Open integrator (no endpoints) for use with problems of no smaller than
 * 7x7.
 * The formula used for the integration (quadrature) is gotten by 
 * extending the trapezoidal rule (a quadrature formula involving two points)
 * to an arbitrary number of points, then modifing it to be open (neglect of
 * endpoints) rather  than closed (inclusion of endpoints). The result is then
 * generalized to two dimensions.
 * This formula is a multidimensional form of equation (4.1.18) from
 * 'Numerical Recipes in C'. A reasonably good derivation of the single
 * dimensional form is given there.
 */

#ifndef PDE_INTEGRATOR_OPEN_PLUS
#define PDE_INTEGRATOR_OPEN_PLUS

class integrator_open_plus
{
 public:
  integrator_open_plus();

  template<class StaticSolution> double operator() (const StaticSolution& solution);
 private:

};

integrator_open_plus::integrator_open_plus()
{
}

template<class StaticSolution>
double integrator_open_plus::operator()(const StaticSolution& solution)
{
  double line;	// integral along a grid line
  double result;	// result of integral
  int I = solution.I();
  int J = solution.J();
  double sx, sy;
  int i, j;

  sx = solution.dx();
  sy = solution.dy();
  result = 0.0;

  double outer = 55.0/24.0;
  double mid = -1.0/6.0;
  double inner = 11.0/8.0;

  // calc first (interior) line
  line = outer*solution.at(1,1);
  line += mid*solution.at(1,2);
  line += inner*solution.at(1,3);
  for(j = 4; j < J-3; ++j)
    line += solution.at(1,j);
  line += inner*solution.at(1,J-3);
  line += mid*solution.at(1,J-2);
  line += outer*solution.at(1,J-1);
  line *= sy;
  result = outer*line;

  // second
  line = outer*solution.at(2,1);
  line += mid*solution.at(2,2);
  line += inner*solution.at(2,3);
  for(j = 4; j < J-3; ++j)
    line += solution.at(2,j);
  line += inner*solution.at(2,J-3);
  line += mid*solution.at(2,J-2);
  line += outer*solution.at(2,J-1);
  line *= sy;
  result += mid*line;

  // third
  line = outer*solution.at(3,1);
  line += mid*solution.at(3,2);
  line += inner*solution.at(3,3);
  for(j = 4; j < J-3; ++j)
    line += solution.at(3,j);
  line += inner*solution.at(3,J-3);
  line += mid*solution.at(3,J-2);
  line += outer*solution.at(3,J-1);
  line *= sy;
  result += inner*line;

  // interior values
  for(i = 4; i < I-3; ++i){
    line = outer*solution.at(i,1);
    line += mid*solution.at(i,2);
    line += inner*solution.at(i,3);
    for(j = 4; j < J-3; ++j){
      line += solution.at(i,j);
    }
    line += inner*solution.at(i,J-3);
    line += mid*solution.at(i,J-2);
    line += outer*solution.at(i,J-1);
    line *= sy;
    result += line;
  }

  // third from last
  line = outer*solution.at(I-3,1);
  line += mid*solution.at(I-3,2);
  line += inner*solution.at(I-3,3);
  for(j = 4; j < J-3; ++j)
    line += solution.at(I-3,j);
  line += inner*solution.at(I-3,J-3);
  line += mid*solution.at(I-3,J-2);
  line += outer*solution.at(I-3,J-1);
  line *= sy;
  result += inner*line;

  // next to last
  line = outer*solution.at(I-2,1);
  line += mid*solution.at(I-2,2);
  line += inner*solution.at(I-2,3);
  for(j = 4; j < J-3; ++j)
    line += solution.at(I-2,j);
  line += inner*solution.at(I-2,J-3);
  line += mid*solution.at(I-2,J-2);
  line += outer*solution.at(I-2,J-1);
  line *= sy;
  result += mid*line;

  // last
  line = outer*solution.at(I-1,1);
  line += mid*solution.at(I-1,2);
  line += inner*solution.at(I-1,3);
  for(j = 4; j < J-3; ++j)
    line += solution.at(I-1,j);
  line += inner*solution.at(I-1,J-3);
  line += mid*solution.at(I-1,J-2);
  line += outer*solution.at(I-1,J-1);
  line *= sy;
  result += outer*line;

  result *= sx;

  return result;

}

#endif	// PDE_INTEGRATOR_OPEN_PLUS
