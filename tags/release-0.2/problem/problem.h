/* problem, abstract class: defines a finite differencing problem.
 *
 */

#ifndef PDE_PROBLEM
#define PDE_PROBLEM

class problem
{
public:
  virtual int I() const = 0;	// points in the first var
  virtual int J() const = 0;	// points in the second var
  virtual double dx() const = 0;	// spacing in first var
  virtual double dy() const = 0;	// spacing in second var
  virtual double x0() const = 0;
  virtual double y0() const = 0;
  virtual double a(int , int) const = 0;
  virtual double b(int , int) const = 0;
  virtual double c(int , int) const = 0;
  virtual double d(int , int) const = 0;
  virtual double e(int , int) const = 0;
  virtual double f(int , int) const = 0;
  virtual double& u(int, int) = 0;	// interior values, faster
  virtual double at(int, int) const = 0;// correct boundary values and checking
};
/*
 * u(int,int) need not return correct values on the boundaries (no bounds
 * checking requirement) and should return a reference.
 * at(int,int) should return correct values on the boundary but may be
 * slower then u(int,int) by a small bounded additive factor.
 * u(int,int) and at(int,int) should return the same values for interior
 * points.
 */
#endif	//PDE_PROBLEM
