/* a transformation which squares the passed 'Static Solution'.
 * the template type for this class is the 'Static Solution' which will be
 * transformed.
 */ 

#include <cmath>

template<class StaticSolution>
class square {

 public:
  square(const StaticSolution& solution);

  int I() const {return sol.I();}
  int J() const {return sol.J();}
  double dx() const {return sol.dx();}
  double dy() const {return sol.dy();}
  double x0() const {return sol.x0();}
  double y0() const {return sol.y0();}
  double at(int i, int j);

 private:
  StaticSolution sol;

};
