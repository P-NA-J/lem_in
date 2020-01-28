#!/bin/bash

read -p "How many tests do u wanna perform ?" nb_tests

i=0


while [[ $i -lt $nb_tests ]] 
do
	echo $i
	./generator --big-superposition > $i  
	grep "lines required" $i
	./lem-in < $i | wc -l 
	time ./lem-in < $i > pr | grep user
	i=$((i+1)) 
done
