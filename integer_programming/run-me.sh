export GUROBI_HOME="/opt/gurobi752/linux64"
export PATH="${PATH}:${GUROBI_HOME}/bin"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${GUROBI_HOME}/lib"
export GRB_LICENSE_FILE="$HOME/gurobi.lic"

mkdir result
for file in ../instances/*.txt; do
	printf "$file \n"
	./model $file
	printf "\n"
done