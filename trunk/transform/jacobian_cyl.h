/* a transformation resulting from the multiplication of a problem
 * by the jacobian for cylidrical coordinates (r*sin(theta)).
 */ 

template <class StaticSolution>
class jacobian_cyl {

 public:
  jacobian_cyl(StaticSolution solution);

  double at(int i, int j);

 private:
  StaticSolution sol;

};
