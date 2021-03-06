/* class for use as a function object which increments its value every time
 * it's called (created for use with the 'generate' function).
 */
#ifndef PDE_NEXT
#define PDE_NEXT

class next{
public:
  next(int value);
  next();
  int operator()();
private:
  int val;
};

next::next(int value) : val(value) {}
next::next() : val(0) {}

int next::operator()()
{ return val++; }

#endif	//PDE_NEXT
