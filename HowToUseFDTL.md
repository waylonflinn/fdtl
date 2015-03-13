# Using the Finite Difference Template Library #

# Introduction #


## Make File ##


## Input File ##

The input file describes the boundary conditions. All boundaries are rectangular. Each side may be assigned either Dirichlet (value) or Neumann (value of derivative) conditions. Both may occur in the same file.

For a BEC with axial symmetry, the boundary conditions are that the wave function go to zero at large r or large (positive or negative) z, and that it be continuous when z=0 or r=0.

Each line in the file...

  * specifies the condition along an edge of the bounding rectangle.
  * may be preceded by a line containing one of the words 'Dirichlet' or 'Neumann' to indicate that the line following specifies a boundary condition of that type.
  * maps to a boundary based on order. Boundaries are specified clockwise starting at the top; thus, the mapping is as follows:
    * top (y = ymax)
    * right (x = xmax)
    * bottom (y = ymin)
    * left (x = xmin)

Each character in a line...

  * must be numeric or whitespace which, respectively,
    * specifies the value at a particular point along the boundary
    * separates two of those values

The following is an example which specifies mixed (Neumann and Dirichlet) conditions.

```
Dirichlet
0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1
Dirichlet
0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1
Neumann
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
Neumann
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```