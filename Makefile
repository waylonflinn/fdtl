# makefile for test of pde code
# $^ gives (path matched) prerequisites
# $< is the first prerequisite
# $@ is the target
# $(<D) is the directory part of the first prerequisite

inter_obj = argument.o option.o command_line.o interface.o
com_obj = problem_basic.o residual_norm.o boundary.o $(inter_obj)
sor_l_obj = sor_l.o successive_overrelaxation.o laplace.o $(com_obj)
gs_l_obj = gs_l.o gauss_seidel.o laplace.o $(com_obj)
dir_algorithm = ./algorithm/
dir_problem = ./problem/
dir_interface = ./interface/
VPATH = $(dir_algorithm):$(dir_problem):$(dir_interface)

ifeq ($(MAKECMDGOALS),debug)
 CPPFLAGS = -g -I $(dir_algorithm) -I $(dir_problem)
else
 CPPFLAGS = -I$(dir_algorithm) -I$(dir_problem) -I$(dir_interface)
endif

.PHONY : all clean debug

all : sor_l gs_l

sor_l : sor_l.o $(sor_l_obj)
	g++ -o $@ $(CPPFLAGS) $^

sor_l.o : sor_l.cpp
	g++ -c $(CPPFLAGS) $<

gs_l : $(gs_l_obj)
	g++ -o $@ $(CPPFLAGS) $^

gs_l.o : gs_l.cpp
	g++ -c $(CPPFLAGS) $<

problem_basic.o : problem_basic.cpp problem_basic.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

laplace.o : laplace.cpp laplace.h problem_basic.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

gauss_seidel.o: gauss_seidel.cpp gauss_seidel.h goal.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

residual_norm.o: residual_norm.cpp residual_norm.h goal.h problem.h
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
boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

clean :
	rm gs_l *.o

debug : $(sor_l_obj)
	g++ -o gs_l $(CPPFLAGS) $^
