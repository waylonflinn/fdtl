# makefile for test of pde code
# $^ gives (path matched) prerequisites
# $< is the first prerequisite
# $@ is the target
# $(<D) is the directory part of the first prerequisite

## object sets
# interface objects
inter_obj = argument.o option.o command_line.o interface.o
# common objects
com_obj = problem_basic.o solver_basic.o residual_norm.o boundary.o \
 $(inter_obj)
# successive overrelaxation on laplace's equation
sor_l_obj = successive_overrelaxation.o laplace.o interface_sor.o $(com_obj)
# gauss seidel on laplace's equation
gs_l_obj = gauss_seidel.o laplace.o $(com_obj)
# multigrid on laplace's equation
mlt_l_obj = multigrid.o bilinear_interpolation.o half_weighting.o \
 gauss_seidel.o laplace.o interface_mlt.o $(com_obj)
# gauss seidel on the simple harmonic oscillator
gs_sho_obj = gauss_seidel.o simple_harmonic_oscillator.o interface_sho.o \
 solution_norm.o $(com_obj)
# successive overrelaxation on the simple harmonic oscillator
sor_sho_obj = successive_overrelaxation.o simple_harmonic_oscillator.o \
 interface_sor_sho.o $(com_obj)
# gauss seidel on a gross pitaevskii equation
gs_gpe_obj = gauss_seidel.o gross_pitaevskii.o interface_gpe.o  $(com_obj)
# gauss seidel on a gross pitaevskii equation in cartesion coordinates
gs_gpe_cart_obj = gauss_seidel.o gross_pitaevskii_cart.o interface_gpe.o \
 solution_norm.o $(com_obj)
# multigrid on a gross pitaevskii equation
mlt_gpe_obj = multigrid.o bilinear_interpolation.o half_weighting.o \
 interface_mlt_gpe.o $(gs_gpe_obj)
# multigrid on a gross pitaevskii equation in cartesian coordinates
mlt_gpe_cart_obj= multigrid.o bilinear_interpolation.o half_weighting.o \
 interface_mlt_gpe_cart.o $(gs_gpe_cart_obj)
# eigenvalue solver
eig_obj = multigrid.o bilinear_interpolation.o half_weighting.o \
 interface_eig.o $(gs_gpe_obj)

## directories
dir_algorithm = ./algorithm/
dir_problem = ./problem/
dir_solver = ./solver/
dir_solution = ./solution/
dir_goal = ./goal/
dir_transform = ./transform/
dir_integrator = ./integrator/
dir_include = ./include/
dir_interface = ./interface/
VPATH = $(dir_solver):$(dir_solution):$(dir_goal):$(dir_include):$(dir_interface):$(dir_transform):$(dir_integrator)

ifeq ($(MAKECMDGOALS),debug)
 CPPFLAGS = -g -frepo -I$(dir_solver) -I$(dir_solution) -I$(dir_goal) -I$(dir_include) -I$(dir_interface) -I$(dir_transform) -I$(dir_integrator)
else
 CPPFLAGS = -frepo -I$(dir_solver) -I$(dir_solution) -I$(dir_goal) -I$(dir_include) -I$(dir_interface) -I$(dir_transform) -I$(dir_integrator)
endif

.PHONY : all clean debug

# phony targets

all :  gs_l sor_l mlt_l gs_sho sor_sho gs_gpe mlt_gpe

clean :
	rm gs_l sor_l mlt_l gs_sho sor_sho gs_gpe mlt_gpe *.o

debug : all

# executables

eig_cart : eig_cart.o $(mlt_gpe_cart_obj)
	g++ -o $@ $(CPPFLAGS) $^

eig_cart.o : eig_cart.cpp $(mlt_gpe_cart_obj)
	g++ -c $(CPPFLAGS) $<

eig : eig.o $(eig_obj)
	g++ -o $@ $(CPPFLAGS) $^

eig.o : eig.cpp $(eig_obj)
	g++ -c $(CPPFLAGS) $<

sor_l : sor_l.o $(sor_l_obj)
	g++ -o $@ $(CPPFLAGS) $^

sor_l.o : sor_l.cpp $(sor_l_obj)
	g++ -c $(CPPFLAGS) $<

gs_l : gs_l.o $(gs_l_obj)
	g++ -o $@ $(CPPFLAGS) $^

gs_l.o : gs_l.cpp $(gs_l_obj)
	g++ -c $(CPPFLAGS) $<

gs_sho : gs_sho.o $(gs_sho_obj)
	g++ -o $@ $(CPPFLAGS) $^

gs_sho.o : gs_sho.cpp $(gs_sho_obj)
	g++ -c $(CPPFLAGS) $<

sor_sho : sor_sho.o $(sor_sho_obj)
	g++ -o $@ $(CPPFLAGS) $^

sor_sho.o : sor_sho.cpp $(sor_sho_obj)
	g++ -c $(CPPFLAGS) $<

gs_gpe : gs_gpe.o $(gs_gpe_obj)
	g++ -o $@ $(CPPFLAGS) $^

gs_gpe.o : gs_gpe.cpp $(gs_gpe_obj)
	g++ -c $(CPPFLAGS) $<

mlt_l : mlt_l.o $(mlt_l_obj)
	g++ -o $@ $(CPPFLAGS) $^

mlt_l.o : mlt_l.cpp $(mlt_l_obj)
	g++ -c $(CPPFLAGS) $<

mlt_gpe : mlt_gpe.o $(mlt_gpe_obj)
	g++ -o $@ $(CPPFLAGS) $^

mlt_gpe.o : mlt_gpe.cpp $(mlt_gpe_obj)
	g++ -c $(CPPFLAGS) $<

mlt_gpe_cart : mlt_gpe_cart.o $(mlt_gpe_cart_obj)
	g++ -o $@ $(CPPFLAGS) $^

mlt_gpe_cart.o : mlt_gpe_cart.cpp $(mlt_gpe_cart_obj)
	g++ -c $(CPPFLAGS) $<

# problems

boundary.o : boundary.cpp boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

problem_basic.o : problem_basic.cpp problem_basic.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

laplace.o : laplace.cpp laplace.h problem_basic.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

simple_harmonic_oscillator.o: simple_harmonic_oscillator.cpp \
  simple_harmonic_oscillator.h problem_basic.cpp problem_basic.h \
  problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

gross_pitaevskii.o: gross_pitaevskii.cpp gross_pitaevskii.h \
  problem_basic.cpp problem_basic.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

gross_pitaevskii_cart.o: gross_pitaevskii_cart.cpp gross_pitaevskii_cart.h \
  problem_basic.cpp problem_basic.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

# algorithms (solvers/goals)

solver_basic.o: solver_basic.cpp solver_basic.h solver.h
	g++ -c $(CPPFLAGS) $< -o $@

gauss_seidel.o: gauss_seidel.cpp gauss_seidel.h goal.h problem.h solver_basic.h
	g++ -c $(CPPFLAGS) $< -o $@

successive_overrelaxation.o : successive_overrelaxation.cpp \
 successive_overrelaxation.h goal.h problem.h solver.h
	g++ -c $(CPPFLAGS) $< -o $@

multigrid.o :multigrid.cpp multigrid.h gauss_seidel.h half_weighting.h \
 bilinear_interpolation.h

residual_norm.o: residual_norm.cpp residual_norm.h goal.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

solution_norm.o: solution_norm.cpp solution_norm.h goal.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

solution_norm_cyl.o: solution_norm_cyl.cpp solution_norm_cyl.h goal.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

bilinear_interpolation.o : bilinear_interpolation.cpp \
 bilinear_interpolation.h operator_prolong.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

half_weighting.o : half_weighting.cpp half_weighting.h operator_restrict.h \
 problem.h
	g++ -c $(CPPFLAGS) $< -o $@

# interface

argument.o : argument.cpp argument.h
	g++ -c $(CPPFLAGS) $< -o $@

option.o: option.cpp option.h argument.h
	g++ -c $(CPPFLAGS) $< -o $@

command_line.o: command_line.cpp command_line.h option.h argument.h
	g++ -c $(CPPFLAGS) $< -o $@

interface.o: interface.cpp interface.h command_line.h option.h argument.h \
 boundary.h option_set.h
	g++ -c $(CPPFLAGS) $< -o $@

interface_sho.o: interface_sho.cpp interface_sho.h interface.cpp interface.h \
 command_line.h option.h argument.h boundary.h option_set.h option_set_sho.h
	g++ -c $(CPPFLAGS) $< -o $@

interface_sor.o: interface_sor.cpp interface_sor.h interface.cpp interface.h \
 command_line.h option.h argument.h boundary.h option_set.h option_set_sor.h
	g++ -c $(CPPFLAGS) $< -o $@

interface_mlt.o: interface_mlt.cpp interface_mlt.h interface.cpp \
  interface.h  command_line.h option.h argument.h boundary.h option_set.h \
  option_set_mlt.h
	g++ -c $(CPPFLAGS) $< -o $@

interface_sor_sho.o: interface_sor_sho.cpp interface_sor_sho.h \
  interface.cpp interface.h command_line.h option.h argument.h boundary.h \
  option_set.h option_set_sor.h option_set_sho.h
	g++ -c $(CPPFLAGS) $< -o $@

interface_gpe.o: interface_gpe.cpp interface_gpe.h interface.cpp interface.h \
 command_line.h option.h argument.h boundary.h option_set.h option_set_gpe.h
	g++ -c $(CPPFLAGS) $< -o $@

interface_mlt_gpe.o: interface_mlt_gpe.cpp interface_mlt_gpe.h interface.cpp \
 interface.h  command_line.h option.h argument.h boundary.h option_set.h \
 option_set_gpe.h option_set_mlt.h
	g++ -c $(CPPFLAGS) $< -o $@

interface_mlt_gpe_cart.o: interface_mlt_gpe_cart.cpp interface_mlt_gpe_cart.h \
 interface.cpp interface.h  command_line.h option.h argument.h boundary.h \
 option_set.h option_set_gpe.h option_set_mlt.h
	g++ -c $(CPPFLAGS) $< -o $@

interface_eig.o: interface_eig.cpp interface_eig.h interface.cpp interface.h \
 command_line.h option.h argument.h boundary.h option_set.h option_set_eig.h \
 option_set_mlt.h