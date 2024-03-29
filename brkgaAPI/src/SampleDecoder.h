/*
 * SampleDecoder.h
 *
 * Any decoder must have the format below, i.e., implement the method decode(std::vector< double >&)
 * returning a double corresponding to the fitness of that vector. If parallel decoding is to be
 * used in the BRKGA framework, then the decode() method _must_ be thread-safe; the best way to
 * guarantee this is by adding 'const' to the end of decode() so that the property will be checked
 * at compile time.
 *
 * The chromosome inside the BRKGA framework can be changed if desired. To do so, just use the
 * first signature of decode() which allows for modification. Please use double values in the
 * interval [0,1) when updating, thus obeying the BRKGA guidelines.
 *
 *  Created on: Jan 14, 2011
 *      Author: rtoso
 */

#ifndef SAMPLEDECODER_H
#define SAMPLEDECODER_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

typedef struct sol{
  int value;
  std::vector <int> vertices;
} Sol;

typedef struct instance{
	int K;
	int N;
	std::vector<int> clusters;
  std::string instanceName;
	std::vector<std::vector<int> > graph;
	std::vector<int> weight;
} Instance;

class SampleDecoder {
public:
	Instance ins;
	SampleDecoder(char * fn);
	~SampleDecoder();

	double decode(const std::vector< double >& chromosome) const;
	void genFileSol(const std::vector< double >& chromosome);
	std::vector< double > greedyConstructiveHeuristic() const;
private:
	Sol createSolution(const std::vector< double >& chromosome) const;
};

#endif
