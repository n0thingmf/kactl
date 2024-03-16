#!/bin/bash

if [ $# -eq 2 ]; then
	g++-13 "$1.cpp"
	bash Comp.sh $2
else
	echo "No hay la cantidad correcta de parametros"
fi
