/* problem, abstract class: defines a finite differencing problem.
 *
 */

class problem
{
public:
  virtual int I() = 0;
  virtual int J() = 0;
  virtual double a(int , int) = 0;
  virtual double b(int , int) = 0;
  virtual double c(int , int) = 0;
  virtual double d(int , int) = 0;
  virtual double e(int , int) = 0;
  virtual double f(int , int) = 0;
  virtual double& u(int, int) = 0;
};
