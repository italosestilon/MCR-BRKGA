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

int main(int argc, char* argv[]) {
	if (argc < 2) {
    cout << "Usage: ./samplecode filename" << endl;
    return 1;
  }

	clk = clock();
	timeout = 3600;

	SampleDecoder decoder = SampleDecoder(argv[1]);			// initialize the decoder

	const unsigned n = decoder.ins.N; // size of chromosomes
	const unsigned p = 1000;	// size of population
	const double pe = 0.16;		// fraction of population to be the elite-set
	const double pm = 0.08;		// fraction of population to be replaced by mutants
	const double rhoe = 0.65;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 16;	// number of threads for parallel decoding

	const long unsigned rngSeed = 0;	// seed to the random number generator
	MTRand rng(rngSeed);	// initialize the random number generator

	// initialize the BRKGA-based heuristic
	BRKGA< SampleDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);

	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 300;	// run for 1000 gens
	do {
	  std::cout << "Generation " << generation+1 << " of " << MAX_GENS << "\n";
		algorithm.evolve();	// evolve the population for one generation

		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}

		cout << algorithm.getBestFitness()*-1 << endl;
	} while (generation < MAX_GENS);

	decoder.genFileSol(algorithm.getBestChromosome());

	elapsed = ((double) (clock() - clk)) / CLOCKS_PER_SEC;
  cout << "Record: " << algorithm.getBestFitness()*-1 << endl;
  cout << fixed << "Time " << elapsed << endl;

	return 0;
}
