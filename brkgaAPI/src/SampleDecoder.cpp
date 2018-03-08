/*
 * SampleDecoder.cpp
 *
 *  Created on: Jan 14, 2011
 *      Author: rtoso
 */

#include "SampleDecoder.h"

#ifndef PATHSOL
#define PATHSOL "brkgaAPI/solutions"
#endif


using namespace std;

std::string getFileName(const std::string& s) {

   char sep = '/';

	 #ifdef _WIN32
   	sep = '\\';
	 #endif

   std::string aux;

   size_t i = s.rfind(sep, s.length());
   if (i != std::string::npos) {
      aux = s.substr(i+1, s.length() - i);
      i = aux.rfind('.', aux.length());
      if (i != std::string::npos){
        return (aux.substr(0, i));
      }
   }

   return("");
}


SampleDecoder::SampleDecoder(char * fn) {
  ifstream infile(fn);

  ins.instanceName = getFileName(fn);

  infile >> ins.K;

	ins.N = 0;

	ins.clusters.resize(ins.K);

	for(int i=0; i<ins.K; i++){
		infile >> ins.clusters[i];
		ins.N += ins.clusters[i];
	}

	ins.graph.resize(ins.N);

	for(int i=0; i<ins.N; i++){
		ins.graph[i].resize(ins.N, 0);
	}

	int u, v, w;

	ins.weight.resize(ins.N, 0);

  while(infile >> u >> v >> w){
    ins.graph[u][v] = w;
		ins.graph[v][u] = w;
		ins.weight[u] += w;
		ins.weight[v] += w;
  }

	infile.close();
}

SampleDecoder::~SampleDecoder() { }

std::vector< double > SampleDecoder::greedyConstructiveHeuristic() const{
	std::vector< double > chromosome;
	chromosome.resize(ins.N, 0);

	int max[ins.K];

	for(int i=0, c=0; i<ins.K; i++){
		max[i] = c;
		for(int j=1; j<ins.clusters[i]; j++){
			if(ins.weight[c+j] > ins.weight[max[i]]){
				max[i] = c+j;
			}
		}
		c += ins.clusters[i];
	}


	for(int i=0; i<ins.K; i++){
		chromosome[max[i]] = 1;
	}

	cout << decode(chromosome)*-1 << endl;

	return chromosome;
}

Sol SampleDecoder::createSolution(const std::vector< double >& chromosome) const{
  Sol sol;
	sol.value = 0;
	sol.vertices.resize(ins.K);

	for(int i=0, c=0; i<ins.K; i++){
		sol.vertices[i] = c;
		for(int j=1; j<ins.clusters[i]; j++){
			if(chromosome[c+j] > chromosome[sol.vertices[i]]){
				sol.vertices[i] = c+j;
			}
		}
		c += ins.clusters[i];
	}

	for(int i=0; i<ins.K; i++){
		int u = sol.vertices[i];
		for(int j=i+1; j<ins.K; j++){
			int v = sol.vertices[j];
			sol.value += ins.graph[u][v];
		}
	}

  return sol;
}

double SampleDecoder::decode(const std::vector< double >& chromosome) const {
  Sol sol;

  sol = createSolution(chromosome);

	return sol.value*-1;
}

void SampleDecoder::genFileSol(const std::vector< double >& chromosome){
  Sol sol;

  sol = createSolution(chromosome);

  double result = sol.value;

  char* fn = new char[256];

  sprintf(fn, "%s/%s.sol", PATHSOL, ins.instanceName.c_str());

  int chromo[ins.N];

  for(int i=0; i<ins.N; i++){
    chromo[i] = 0;
  }

  for(int i=0, size = sol.vertices.size(); i<size; i++){
    chromo[sol.vertices[i]] = 1;
  }

  ofstream opf;
  opf.open(fn);

  opf << result << endl;

  for(int i=0; i<ins.N; i++){
    opf << chromo[i] << endl;
  }

  opf.close();
}
