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

	timeout = 3600;
	double totalTime = 0;
	double totalV = 0;

	int c = 1000;

	SampleDecoder decoder = SampleDecoder(argv[1]);			// initialize the decoder

	const unsigned n = decoder.ins.K; // size of chromosomes
	const unsigned p = 1000;	// size of population
	const double pe = 0.16;		// fraction of population to be the elite-set
	const double pm = 0.08;		// fraction of population to be replaced by mutants
	const double rhoe = 0.65;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 3;	// number of threads for parallel decoding

	const long unsigned rngSeed = 0;	// seed to the random number generator
	MTRand rng(rngSeed);	// initialize the random number generator

	while(c--){
		// initialize the BRKGA-based heuristic
		BRKGA< SampleDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);
		unsigned generation = 0;		// current generation
		const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
		const unsigned X_NUMBER = 2;	// excichange top 2 best
		const unsigned MAX_GENS = 500;	// run for 1000 gens

		clk = clock();
		do {
		  	//std::cout << "Generation " << generation+1 << " of " << MAX_GENS << "\n";
			algorithm.evolve();	// evolve the population for one generation

			if((++generation) % X_INTVL == 0) {
				algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
			}

			//cout << algorithm.getBestFitness()*-1 << endl;
		} while (generation < MAX_GENS);

		elapsed = ((double) (clock() - clk)) / CLOCKS_PER_SEC;

		totalTime += elapsed;
		totalV += algorithm.getBestFitness()*-1;

		cout << algorithm.getBestFitness()*-1 << endl;
	}
	//decoder.genFileSol(algorithm.getBestChromosome());


  cout << "Record: " << totalV/1000.0 << endl;
  cout << fixed << "Time " << totalTime/1000.0 << endl;

	return 0;
}
