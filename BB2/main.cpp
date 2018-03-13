#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <time.h>

using namespace std;

vector<vector<int> > weight;
vector<int> sets;
vector<int> w_max;
vector<pair<int, int> > w_vertex;
vector<int> min_w;
vector<int> size;
vector<vector<int> > max_edge;
vector<vector<int> > maximum_edges_vertex_per_cluster;
int K, N;
long long int subp = 0;
long long int maxSubp = 1;
int timeout;
double elapsed;
double lastElapsed;
clock_t clk;
string instanceName;

int record = 0;
vector<int> s_max;

string getFileName(const string& s) {

   char sep = '/';

	 #ifdef _WIN32
   	sep = '\\';
	 #endif

   string aux;

   size_t i = s.rfind(sep, s.length());
   if (i != string::npos) {
      aux = s.substr(i+1, s.length() - i);
      i = aux.rfind('.', aux.length());
      if (i != string::npos){
        return (aux.substr(0, i));
      }
   }

   return("");
}

void genFileSol(){

  char* fn = new char[256];

  sprintf(fn, "%s/%s.txt", "BB2/solutions/", instanceName.c_str());

  int chromo[N];

  for(int i=0; i<N; i++){
    chromo[i] = 0;
  }

  for(int i=0, size = s_max.size(); i<size; i++){
    chromo[s_max[i]] = 1;
  }

  ofstream opf;
  opf.open(fn);

  opf << record << endl;

  for(int i=0; i<N; i++){
    opf << chromo[i] << endl;
  }

  opf.close();
}

void readFile(char * fn) {
  ifstream infile(fn);

  instanceName = getFileName(fn);

  infile >> K;

  N = 0;

  size.resize(K);

  w_max.resize(K);

  min_w.resize(K);

  max_edge.resize(K);

  for(int i=0, c=0; i<K; i++){
    infile >> size[i];
    N += size[i];
    maxSubp *= size[i];
    min_w[i] = 100000;
    max_edge[i].resize(K, 0);
    max_edge[i][i] = 0;
  }


  maximum_edges_vertex_per_cluster.resize(N);
  weight.resize(N);
  sets.resize(N);
  w_vertex.resize(N, make_pair(0,0));

  for(int i = 0; i < N; i++){
    w_vertex[i].second = i;
    weight[i].resize(N, 0);
    maximum_edges_vertex_per_cluster[i].resize(K, 0);
  }

  for(int i=0, c=0; i<K; i++){
    for(int j=0; j<size[i]; j++){
      sets[c + j] = i;
    }
    w_max[i] = c;
    c += size[i];
  }

  int u, v, w;

  while(infile >> u >> v >> w){
    weight[u][v] = weight[v][u] = w;
    w_vertex[u].first += w;
    w_vertex[v].first += w;

    if(w > 0 && w < min_w[sets[u]]){
      min_w[sets[u]] = w;
    }

    if(w > 0 && w < min_w[sets[v]]){
      min_w[sets[v]] = w;
    }

    if(w > maximum_edges_vertex_per_cluster[u][sets[v]]){
      maximum_edges_vertex_per_cluster[u][sets[v]] = w;
    }

    if(w > maximum_edges_vertex_per_cluster[v][sets[u]]){
      maximum_edges_vertex_per_cluster[v][sets[u]] = w;
    }

    if(w > max_edge[sets[u]][sets[v]] && sets[u] != sets[v]){
      max_edge[sets[u]][sets[v]] = max_edge[sets[v]][sets[u]] = w;
    }
  }

  for(int i=0; i<N; i++){
    if(w_vertex[w_max[sets[i]]].first < w_vertex[i].first){
      w_max[sets[i]] = i;
    }
  }
}

void readFileSolution(char * fn){
  ifstream infile(fn);

  int x;
  s_max.clear();


  infile >> record;

  cout << fn << endl;

  cout << record << endl;

  for(int i=0; i<N; i++){
    infile >> x;
    if(x){
      s_max.push_back(i);
    }
  }
}

void lower_bound(){
  s_max.clear();

  for(int i=0; i<K; i++){
    s_max.push_back(w_max[i]);
  }

  int size_s = s_max.size();

  int value = 0;
  for(int i = 0; i < size_s; i++){
    for(int j = i+1; j < size_s; j++){
      value += weight[s_max[i]][s_max[j]];
    }
  }

  record = value;
}

int upper_bound(vector<int> s, int level){
  int size_s = s.size();

  int value = 0;

  for(int i = level; i < K; i++){
    for(int j=i+1; j < K; j++){
      value += max_edge[i][j];
    }
  }

  for(int i = 0; i < size_s; i++){
    int index = s[i];
    for(int j = level; j < K; j++){
      value += maximum_edges_vertex_per_cluster[index][j];
    }
  }

  return value;
}

void branch_and_bound(vector<int> s, vector<int> c, int level){
  subp++;

  int size_s = s.size();
  int size_c = c.size();


  int value = 0;

  for(int i = 0; i < size_s; i++){
    for(int j = i+1; j < size_s; j++){
      value += weight[s[i]][s[j]];
    }
  }

  elapsed = ((double) (clock() - clk)) / CLOCKS_PER_SEC;

  if(elapsed > timeout){
    cout << "Record: " << record << endl;
    cout << "Subp: " << subp << endl;
    cout << fixed << "Time " << elapsed << endl;


    int size_s = s_max.size();
    for(int i=0; i<size_s; i++){
      cout << s_max[i] << " ";
    }

    cout << endl;

    genFileSol();

    exit(1);
  }

  if(size_s == K){
    if(value > record){
      cout << "solution value: " << value << " | Subp " << subp << fixed << " | Time " << elapsed << "s" << endl;
      lastElapsed = elapsed;
      record = value;
      s_max.clear();
      for(int i = 0; i < size_s; i++){
        s_max.push_back(s[i]);
      }
    }

    return;
  }

  int ub = upper_bound(s, level) + value;

  //cout << ub << endl;

  if(ub <= record){
    return;
  }

  vector<int> new_s(level+1);
  vector<int> new_c;

  for(int j = size[level]; j < size_c; j++){
    new_c.push_back(c[j]);
  }

  for(int i = 0; i < level; i++){
    new_s[i] = s[i];
  }

  for(int i = 0; i < size[level]; i++){
    new_s[level] = c[i];

    branch_and_bound(new_s, new_c, level+1);
  }

}


int main(int argc, char *argv[]){
  if (argc < 2) {
    cout << "Usage: ./main filename [solution]" << endl;
    return 1;
  }

  readFile(argv[1]);

  clk = clock();
  cout.precision(2);

  timeout = 3600;

  vector<int> s;
  vector<int> c;

  if(argc > 2){
    readFileSolution(argv[2]);
  }else{
    lower_bound();
  }

  //SORTING VERTICES
  for(int i=0, count=0; i<K; i++){
    sort(w_vertex.begin()+count, w_vertex.begin()+count+size[i], greater<pair<int, int> >());
    count += size[i];
  }

  for(int i = 0; i < N; i++){
    c.push_back(w_vertex[i].second);
  }

  cout << "K " << K << endl;

  cout << "MAX SUBP " << maxSubp << endl;

  cout << "LB " << record << endl;

  int ub = upper_bound(s, 0);

  cout << "UB " << ub << endl;

  lastElapsed = 0;

  branch_and_bound(s, c, 0);

  elapsed = ((double) (clock() - clk)) / CLOCKS_PER_SEC;
  cout << "Record: " << record << endl;
  cout << "Subp: " << subp << endl;
  cout << fixed << "Time " << elapsed << endl;

  genFileSol();

  int size_s = s_max.size();
  for(int i=0; i<size_s; i++){
    cout << s_max[i] << " ";
  }

  cout << endl;

  return 0;
}
