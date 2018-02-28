all: model 
	g++  model.cpp -o model -I${GUROBI_HOME}/include -L${GUROBI_HOME}/lib -lgurobi_c++ -lgurobi75

clean:
	rm -f model