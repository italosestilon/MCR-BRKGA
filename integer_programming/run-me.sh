mkdir result
for file in ../instances/*.txt; do
	printf "$file \n"
	./model $file
	printf "\n"
done