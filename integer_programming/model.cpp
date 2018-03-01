#include "gurobi_c++.h"
#include<fstream>

using namespace std;

int c = 3;
vector< vector<int> > m;
vector<int> sets;

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
		sets.push_back(setSize);
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

double upper_bound_linear_relaxation(vector< vector<int> > m, vector<int> sets, vector<int> partial_solution){
	int c = m.size();

	GRBEnv env = GRBEnv();

	GRBModel model = GRBModel(env);

	vector<GRBVar> X;

    for(int i = 0; i < c; i++){
 		X.push_back(model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, "x"));
    }

    vector<vector <GRBVar> > Y (c, vector<GRBVar>(c));
    for(int i = 0; i < c; i++){
        for(int j = i+1; j < c; j++) {
            Y[i][j] = (model.addVar(0.0, 1.0, 0.0, GRB_CONTINUOUS, "y"));
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
    int k = 0;
    int s = sets.size();
    for(int i = 0; i < s; i++){
        GRBLinExpr expr1 = 0.0;
        for(int j = 0; j < sets[i]; j++, k++){
            expr1 += X[k];
        }

        model.addConstr(expr1 <= 1, "c3-s-");
    }

    //04
    for(int i = 0; i < c; i++){
        for(int j = i+1; j < c; j++){
            if(m[i][j] != 0) continue;
            model.addConstr(X[i] + X[j] <= 1, "c3");
        }
    }


    for(int i = 0; i < partial_solution.size(); i++){
    	if(partial_solution[i] == 1){
        	model.addConstr(X[i] == partial_solution[i], "force");
    	}
    }

    //set variables

    cout << "running linear relaxation" << endl;

    model.set(GRB_IntParam_OutputFlag, 0);
    model.setObjective(expr, GRB_MAXIMIZE);
    model.optimize();

    cout << "best bound from linear relaxation " << model.get(GRB_DoubleAttr_ObjVal) << endl;

    return model.get(GRB_DoubleAttr_ObjVal);
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