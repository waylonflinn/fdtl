#include <iostream>
#include <stdlib.h>

#define PI	3.14159265


float tf(double k, double a, double b);
void process_args(int argc, char *argv[]);

double k;	// the interaction parameter
double a;	// the first coefficient in the potential
double b;	// the second coefficient in the potential


int main(int argc, char *argv[])
{
  extern double k, a, b;

  process_args(argc, argv);

  cout << tf(k, a, b) << endl;
}

float tf(double k, double a, double b)
{
  return pow((15 * k)/( 8 * PI), 2.0/5.0) * pow((a * b), 1.0/5.0);
}

void process_args(int argc, char *argv[])
{
  extern double k, a, b;

  k = 1;
  a = 1;
  b = 1;

  while(--argc > 0) {
    if((*++argv)[0] == '-') {	// check the first char of the next arg
      switch ((*argv)[1]) {	// if '-' check the second char
      case 'k' :
	k = atof(*++argv);	// if valid convert the next arg to a float
	break;
      case 'a' :
	a = atof(*++argv);
	break;
      case 'b' :
	b = atof(*++argv);
	break;
      }
    }
  }
}
