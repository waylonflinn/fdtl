# Quick Start #

To get started quickly using the FDTL see the HowTo page.

# Introduction #

The Finite Difference Template Library (FDTL) was created
for the purposes of quickly solving partial differential
equations  using the finite difference method. It is
implemented in C++ using both the object oriented (OO)
paradigm and generic programming techniques (templates).

The project was initially begun to solve a specific type of equation found in low temperature quantum mechanics (a Gross-Pitaevskii equation, a form of Schrodinger’s equation), but was written in such a way as to easily allow the solution of a wide range of partial differential equations.

It current primary goal is to enable those with only an introductory knowledge of the finite difference method (and not necessarily any knowledge of solution methods) to expeditiously create efficient software for solving an equation. It is meant, therefore, to be fast in the sense that the time required for theoretical preparation, development and execution are all small.

# Technical Details #

The project is created in such a way that new solution methods (called 'solvers') can be created and used with existing objects and concepts. Several solvers exist in the current project. These make use of a variety of techniques from numerical methods including: the gauss-seidel method (a variant of the relaxation method) odd-even ordering, chebyshev acceleration and multigrid techniques.