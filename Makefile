# makefile for test of pde code
# $^ gives (path matched) prerequisites
# $< is the first prerequisite
# $@ is the target
# $(<D) is the directory part of the first prerequisite

inter_obj = argument.o option.o command_line.o interface.o
com_obj = problem_basic.o residual_norm.o boundary.o $(inter_obj)
sor_l_obj = successive_overrelaxation.o laplace.o interface_sor.o $(com_obj)
gs_l_obj = gauss_seidel.o laplace.o $(com_obj)
gs_sho_obj = gauss_seidel.o simple_harmonic_oscillator.o interface_sho.o \
 solution_norm.o $(com_obj)
sor_sho_obj = successive_overrelaxation.o simple_harmonic_oscillator.o \
 interface_sor_sho.o $(com_obj)
dir_algorithm = ./algorithm/
dir_problem = ./problem/
dir_interface = ./interface/
VPATH = $(dir_algorithm):$(dir_problem):$(dir_interface)

ifeq ($(MAKECMDGOALS),debug)
 CPPFLAGS = -g -I$(dir_algorithm) -I$(dir_problem) -I$(dir_interface)
else
 CPPFLAGS = -I$(dir_algorithm) -I$(dir_problem) -I$(dir_interface)
endif

.PHONY : all clean debug

all : sor_l gs_l gs_sho sor_sho

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

problem_basic.o : problem_basic.cpp problem_basic.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

laplace.o : laplace.cpp laplace.h problem_basic.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

simple_harmonic_oscillator.o: simple_harmonic_oscillator.cpp \
  simple_harmonic_oscillator.h problem_basic.cpp problem_basic.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

gauss_seidel.o: gauss_seidel.cpp gauss_seidel.h goal.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

residual_norm.o: residual_norm.cpp residual_norm.h goal.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

solution_norm.o: solution_norm.cpp solution_norm.h goal.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

boundary.o : boundary.cpp boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

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

clean :
	rm gs_l sor_l gs_sho *.o

debug : all