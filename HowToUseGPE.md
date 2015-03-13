# Introduction #

This page describes the basics of how to employ the executable for solving the Gross-Pitaevskii equation.

These instructions refer to use of the executable which solves the standard GPE in cylindrical coordinates assuming axial symmetry. It was created to model [BEC](http://en.wikipedia.org/wiki/Bose-Einstein_condensate) behaviour in an anisotropic cylindrical potential. The version which solves the modified GPE functions identically.

Before the executable may be employed it (most likely) must be compiled from source. Instructions for this can be found on the [HowToCompileGPE](HowToCompileGPE.md) page.

# Instructions #
_TODO: expand instructions_
  1. Verify that the input file contains the correct boundary conditions
  1. Determine the options to pass
    * (how is k determined from lambda?)
    * (rule-of-thumb or example for number of points to use?)
  1. Evaluate the output to determine if the answer is sufficiently converged given the number of points used and the size of the bounding box specified.


# Details #

## Input File ##

The input file describes the boundary conditions. All boundaries are rectangular. Each side may be assigned either Dirichlet (value) or Neumann (value of derivative) conditions. Both may occur in the same file.

For a BEC with axial symmetry, the boundary conditions are that the wave function go to zero at large r or large (positive or negative) z, and that it be continuous when r=0. Thus the rectangular boundary conditions are specified on (0,rmax)x(-zmax,zmax). Boundaries are specified clockwise starting at the top; thus, the mapping is as follows:
  * top (`z = zmax`)
  * right (`r = rmax`)
  * bottom (`z = -zmax`)
  * left (`r = 0`)
The input file specifying boundary conditions for an axially-symmetric BEC should be
(Waylon, please verify that this input file is correct for a BEC)
```
Dirichlet
0
Dirichlet
0
Dirichlet
0
Neumann
0
```

## Command Line Arguments ##

To print a usage summary of the command line options to mlt\_gpe

`mlt_gpe -h`

The output of this command yields

mlt\_gpe 

&lt;options&gt;

 

&lt;file&gt;

 where 

&lt;options&gt;

 is zero or more of:
  * -h      print a usage summary
  * -d      print only the hea(d)er information for the solution
  * -I 

&lt;n&gt;

  

&lt;n&gt;

 is the number of points for the first variable (x)
  * -J 

&lt;n&gt;

  

&lt;n&gt;

 is the number of points for the second variable (y)
  * -N 

&lt;n&gt;

  

&lt;n&gt;

 is the number of points for both variables
  * -x 

&lt;x0&gt;

 

&lt;x1&gt;

 

&lt;x0&gt;

 is the mininum for the first variable (x) and 

&lt;x1&gt;

 is the maximum for the first variable (x)
  * -y 

&lt;y0&gt;

 

&lt;y1&gt;

 

&lt;y0&gt;

 is the mininum for the second variable (y)
> > and 

&lt;y1&gt;

 is the maximum for the second variable (y)
  * -S 

&lt;n&gt;

  

&lt;n&gt;

 is the size of the smallest grid
  * -a 

&lt;w&gt;

  

&lt;w&gt;

 is the coefficient to the first variable (x)
  * -b 

&lt;w&gt;

  

&lt;w&gt;

 is the coefficient to the second variable (y)
  * -e 

&lt;w&gt;

  

&lt;w&gt;

 is the eigenvalue
  * -k 

&lt;w&gt;

  

&lt;w&gt;

 is the interaction parameter and 

&lt;file&gt;

 is a properly formatted file to use for the input (or '-').


## Output file ##

_TODO: add this_