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
	$(CPP) $(CFLAGS) $(OBJECTS) -o main 

main.o:
	$(CPP) $(CFLAGS) -c main.cpp

# Remove:
clean:
	rm -f main $(OBJECTS)
