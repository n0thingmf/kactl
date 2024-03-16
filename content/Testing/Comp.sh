#!/bin/bash

g++-13 gen.cpp -o G
g++-13 brute.cpp -o brute
veredict="Accepted"

for((i=0; i<$1; i++)); do
	./G > int
	./a.out < int > out
	./brute < int > out2
	differences=$(diff -w out out2)
	if [ "$differences" != "" ]; then
		veredict="Wrong Answer"
		testcase="$i"
	fi
	if [ "$(cat out)" == "" ]; then
		veredict="Time Limit Exceeded"
		testcase="$i"
	fi
	if [ "$veredict" != "Accepted" ]; then
		break
	fi
done
if [ "$veredict" == "Accepted" ];then
	echo $veredict
else
	echo "$veredict on test $testcase"
fi
