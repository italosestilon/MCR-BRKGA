#include "gurobi_c++.h"
#include<fstream>

using namespace std;

int c = 3;
vector< vector<int> > m;

void readInput(const char* instancePath){

	int s;
	int setSize;
	c = 0;

	ifstream instance;
	instance.open(instancePath);

	if(!instance.is_open()){
		cout << "Ops. Problemas ao ler o arquivo.\n" ;
		return;
	}

	instance >> s;

	for(int i = 0; i < s; i++){
		instance >> setSize;
		c += setSize;
	}


	m = vector< vector<int> >(c, vector<int>(c));

	int a, b, v;

	while(!instance.eof()){
		instance >> a >> b >> v;

		m[a][b] = v;
	}

	instance.close();
}

int main(int argsc, char* argsv[]){

	readInput(argsv[1]);

	GRBEnv env = GRBEnv();

	GRBModel model = GRBModel(env);

	vector<GRBVar> X;

    for(int i = 0; i < c; i++){
 		X.push_back(model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "x"));
    }

    vector<vector <GRBVar> > Y (c, vector<GRBVar>(c));
    for(int i = 0; i < c; i++){
        for(int j = i+1; j < c; j++) {
            Y[i][j] = (model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "y"));
        }
    }

    GRBLinExpr expr = 0.0;
    for(int i = 0; i < c; i++){
        for(int j = i+1; j < c; j++){
            expr += m[i][j] * Y [i][j];
        }
    }


    //01
    for(int i = 0; i < c; i++){
        for(int j = i+1; j < c; j++){
            if(m[i][j] == 0) continue;
            model.addConstr(Y[i][j] <= X[i], "c1");
            model.addConstr(Y[i][j] <= X[j], "c1-2");
        }
    }


    //02
    for(int i = 0; i < c; i++){
        for(int j = i+1; j < c; j++){
            if(m[i][j] == 0) continue;
            model.addConstr(X[i] + X[j] <= Y[i][j] + 1,"c2");
        }
    }

    //03
    for(int i = 0; i < c; i++){
        for(int j = i+1; j < c; j++){
            if(m[i][j] != 0) continue;
            model.addConstr(X[i] + X[j] <= 1, "c3");
        }
    }

    model.setObjective(expr, GRB_MAXIMIZE);
    model.optimize();

	return 0;
}