# Macros:
CPP= g++
#CFLAGS= -O3 -fopenmp
CPATH = ""
CFLAGS= -O3
OBJECTS= main.o
CCFLAGS = -O3 $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) $(SYSTEMCCFLAGS) -fopenmp

# Targets:
all: clean main

main: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o main -I${GUROBI_HOME}/include -L${GUROBI_HOME}/lib -lgurobi_c++ -lgurobi75

main.o:
	$(CPP) $(CFLAGS) -c main.cpp -I${GUROBI_HOME}/include -L${GUROBI_HOME}/lib -lgurobi_c++ -lgurobi75

# Remove:
clean:
	rm -f main $(OBJECTS)
