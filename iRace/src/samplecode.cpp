#include <iostream>
#include "SampleDecoder.h"
#include "MTRand.h"
#include "BRKGA.h"
#include <vector>
#include <time.h>

using namespace std;

int timeout;
double elapsed;
double lastElapsed;
clock_t clk;

int main(int argc, char* argv[]) 
{
	clk = clock();
   
	timeout = 300;

	SampleDecoder decoder = SampleDecoder(argv[1]);	// initialize the decoder

	unsigned n = decoder.ins.N;   // size of chromosomes
	unsigned p = atoi(argv[2]);   // size of population
	double pe = atof(argv[3]);		// fraction of population to be the elite-set
	double pm = atof(argv[4]);		// fraction of population to be replaced by mutants
	double rhoe = atof(argv[5]);	// probability that offspring inherit an allele from elite parent
	unsigned K = atoi(argv[6]);   // number of independent populations
	
   const unsigned MAXT = 16;  // number of threads for parallel decoding

	const long unsigned rngSeed = time(0);	// seed to the random number generator
	MTRand rng(rngSeed);                   // initialize the random number generator

	BRKGA<SampleDecoder, MTRand> algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);

	unsigned generation = 0;		   // current generation
	const unsigned X_INTVL = 100;	   // exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	   // exchange top 2 best
	const unsigned MAX_GENS = atoi(argv[7]);	// run for 1000 gens
   
	do {
	   
      //std::cout << "Generation " << generation+1 << " of " << MAX_GENS << "\n";
		
      algorithm.evolve();	// evolve the population for one generation

		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}

	} while (generation < MAX_GENS);

	decoder.genFileSol(algorithm.getBestChromosome());

   elapsed = ((double) (clock() - clk)) / CLOCKS_PER_SEC;
   
   printf("%d %.0lf", (int)algorithm.getBestFitness(), elapsed);
    
   //cout << "Record: " << algorithm.getBestFitness()*-1 << endl;
   //cout << fixed << "Time " << elapsed << endl;

	return 0;
}
