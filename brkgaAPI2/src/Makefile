# Macros:
CPP= g++
#CFLAGS= -O3 -fopenmp
CPATH = ""
CFLAGS= -O3 -fopenmp
OBJECTS= SampleDecoder.o samplecode.o
CCFLAGS = -O3 $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) $(SYSTEMCCFLAGS) -fopenmp

# Targets:
all: clean samplecode

samplecode: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o samplecode

SampleDecoder.o:
	$(CPP) $(CFLAGS) -c SampleDecoder.cpp samplecode.cpp

# Remove:
clean:
	rm -f sampledecode $(OBJECTS)
