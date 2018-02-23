#include <iostream>
#include "SampleDecoder.h"
#include "MTRand.h"
#include "BRKGA.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc < 2) {
    cout << "Usage: ./samplecode filename" << endl;
    return 1;
  }

	std::vector<double> solutions;

	SampleDecoder decoder = SampleDecoder(argv[1]);			// initialize the decoder

	const unsigned n = decoder.ins.N; // size of chromosomes
	const unsigned p = 1000;	// size of population
	const double pe = 0.20;		// fraction of population to be the elite-set
	const double pm = 0.10;		// fraction of population to be replaced by mutants
	const double rhoe = 0.70;	// probability that offspring inherit an allele from elite parent
	const unsigned K = 3;		// number of independent populations
	const unsigned MAXT = 16;	// number of threads for parallel decoding

	const long unsigned rngSeed = 0;	// seed to the random number generator
	MTRand rng(rngSeed);	// initialize the random number generator

	// initialize the BRKGA-based heuristic
	BRKGA< SampleDecoder, MTRand > algorithm(n, p, pe, pm, rhoe, decoder, rng, K, MAXT);

	unsigned generation = 0;		// current generation
	const unsigned X_INTVL = 100;	// exchange best individuals at every 100 generations
	const unsigned X_NUMBER = 2;	// exchange top 2 best
	const unsigned MAX_GENS = 1000;	// run for 1000 gens
	do {
	  std::cout << "Generation " << generation+1 << " of " << MAX_GENS << "\n";
		algorithm.evolve();	// evolve the population for one generation

		if((++generation) % X_INTVL == 0) {
			algorithm.exchangeElite(X_NUMBER);	// exchange top individuals
		}

		solutions.push_back(algorithm.getBestFitness()*-1);
	} while (generation < MAX_GENS);

	std::cout << "Best solution found has objective value = "
	 		<< algorithm.getBestFitness()*-1 << std::endl;

	decoder.genFileSol(algorithm.getBestChromosome());

	return 0;
}
