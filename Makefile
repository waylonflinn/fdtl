# makefile for test of pde code
# $^ gives (path matched) prerequisites
# $< is the first prerequisite
# $@ is the target
# $(<D) is the directory part of the first prerequisite

objects = gs_l.o gauss_seidel.o laplace.o residual_norm.o boundary.o
dir_algorithm = ./algorithm/
dir_problem = ./problem/
dir_interface = ./interface/
VPATH = $(dir_algorithm):$(dir_problem):$(dir_interface)

ifeq ($(MAKECMDGOALS),debug)
 CPPFLAGS = -g -I $(dir_algorithm) -I $(dir_problem)
else
 CPPFLAGS = -I $(dir_algorithm) -I $(dir_problem)
endif


gs_l : $(objects)
	g++ -o gs_l $(CPPFLAGS) $^

gs_l.o : gs_l.cpp
	g++ -c $(CPPFLAGS) $<

gauss_seidel.o: gauss_seidel.cpp gauss_seidel.h goal.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

laplace.o : laplace.cpp laplace.h problem.h boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

residual_norm.o: residual_norm.cpp residual_norm.h goal.h problem.h
	g++ -c $(CPPFLAGS) $< -o $@

boundary.o : boundary.cpp boundary.h
	g++ -c $(CPPFLAGS) $< -o $@

.PHONY : clean debug

clean :
	rm gs_l.exe *.o

debug : $(objects)
	g++ -o gs_l $(CPPFLAGS) $^