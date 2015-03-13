# Introduction #

This page describes how to compile the executable for solving the Gross-Pitaevskii equation on various platforms. The following platforms are known to be compatible.

  * GCC 4.1.2
    * Fedora Core 8
    * Red Hat Enterprise Linux 5

The following steps will produce an executable named `mlt_gpe`. An explanation of it's use and applicability can be found on the [HowToUseGPE](HowToUseGPE.md) page.

# GCC 4.1.2 #

  1. download the source using subversion as described on the  [Source Page](http://code.google.com/p/fdtl/source/checkout)
  1. change to the directory created in the step above
    * `cd fdtl` (if downloading anonymously, `cd fdtl-read-only`)
  1. type `make mlt_gpe`