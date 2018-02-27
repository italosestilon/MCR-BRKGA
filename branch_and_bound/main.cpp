#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

#define MAX_V_NUMBER 20000

int weight[MAX_V_NUMBER][MAX_V_NUMBER];
int group[MAX_V_NUMBER];
vector<int> w_max;
vector<pair<int, int> > w_vertex;
vector<int> size;
int K, N;
long long int subp = 0;

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

void readFile(char * fn) {
  ifstream infile(fn);

  string instanceName = getFileName(fn);

  infile >> K;

  N = 0;

  size.resize(K);

  w_max.resize(K);

  for(int i=0, c=0; i<K; i++){
    infile >> size[i];
    N += size[i];
  }

  w_vertex.resize(N, make_pair(0,0));

  for(int i = 0; i < N; i++){
    w_vertex[i].second = i;
    for(int j = 0; j < N; j++){
      weight[i][j] = 0;
    }
  }

  for(int i=0, c=0; i<K; i++){
    for(int j=0; j<size[i]; j++){
      group[c + j] = i;
    }
    w_max[i] = c+i;
    c += size[i];
  }

  int u, v, w;

  while(infile >> u >> v >> w){
    weight[u][v] = w;
    weight[v][u] = w;
    w_vertex[u].first += w;
    w_vertex[v].first += w;
  }

  for(int i=0; i<N; i++){
    if(w_vertex[w_max[group[i]]].first < w_vertex[i].first){
      w_max[group[i]] = i;
    }
  }
}

void readFileSolution(char * fn){
  ifstream infile(fn);

  int x;
  s_max.clear();

  for(int i=0; i<N; i++){
    infile >> x;
    if(x){
      s_max.push_back(i);
    }
  }

  int size_s = s_max.size();

  int value = 0;
  for(int i = 0; i < size_s; i++){
    for(int j = 0; j < size_s; j++){
      value += weight[s_max[i]][s_max[j]];
    }
  }

  record = value/2;
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

int upper_bound(vector<int> s, vector<int> c){
  int size_c = c.size();
  int size_s = s.size();

  int group_UB[K];

  for(int i = 0; i < K; i++){
    group_UB[i] = 0;
  }

  for(int i = 0; i < size_c; i++){
    int w = 0;
    for(int j = 0; j < size_c; j++){
      w += weight[c[i]][c[j]];
    }

    for(int j = 0; j < size_s; j++){
      w += weight[c[i]][s[j]];
    }

    if(group_UB[group[c[i]]] < w){
      group_UB[group[c[i]]] = w;
    }
  }

  int value = 0;

  for(int i = 0; i < K; i++){
    value += group_UB[i];
  }

  return value;
}

void branch_and_bound(vector<int> s, vector<int> c){
  subp++;

  int size_s = s.size();
  int size_c = c.size();

  int value = 0;
  for(int i = 0; i < size_s; i++){
    for(int j = i+1; j < size_s; j++){
      value += weight[s[i]][s[j]];
    }
  }

  value = value;

  if(size_s == K){
    if(value > record){
      cout << "improving solution value: " << value << endl;
      record = value;
      s_max.clear();
      for(int i = 0; i < size_s; i++){
        s_max.push_back(s[i]);
      }
    }
  }

  int ub = upper_bound(s, c);

  if(ub + value <= record){
    return;
  }

  vector<int> new_s(size_s+1);
  vector<int> new_c;

  for(int i = 0; i < size_s; i++){
    new_s[i] = s[i];
  }

  for(int i = 0; i < size_c; i++){
    new_s[size_s] = c[i];
    new_c.clear();

    for(int j = 0; j < size_c; j++){
      if(group[c[i]] != group[c[j]]){
        new_c.push_back(c[j]);
      }
    }

    branch_and_bound(new_s, new_c);
  }

}


int main(int argc, char *argv[]){
  if (argc < 2) {
    cout << "Usage: ./main filename [solution]" << endl;
    return 1;
  }

  readFile(argv[1]);

  vector<int> s;
  vector<int> c;

  for(int i = 0; i < N; i++){
    c.push_back(w_vertex[i].second);
  }


  if(argc > 2){
    readFileSolution(argv[2]);
  }else{
    lower_bound();
  }
  //SORTING VERTICES
  sort(w_vertex.begin(), w_vertex.end(), greater<pair<int, int> >());

  cout << "LB " << record << endl;

  int ub = upper_bound(s, c);

  cout << "UB " << ub << endl;

  branch_and_bound(s, c);

  cout << record << endl;
  cout << subp << endl;


  int size_s = s_max.size();
  for(int i=0; i<size_s; i++){
    cout << s_max[i] << " ";
  }

  cout << endl;

  return 0;
}
