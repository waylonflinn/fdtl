/* The formula used for the integration (quadrature) is gotten by 
 * extending the trapezoidal rule (a quadrature formula involving two points)
 * to an arbitrary number of points, then modifing it to be open (neglect of
 * endpoints) rather  than closed (inclusion of endpoints). The result is then
 * generalized to two dimensions.
 * This formula is a multidimensional form of equation (4.1.16) from
 * 'Numerical Recipes in C'. A reasonably good derivation of the single
 * dimensional form is given there.
 */

class integrator_open_basic
{
 public:
  integrator_open_basic();

  template<class StaticSolution> double operator() (const StaticSolution& solution);
 private:

};
