all:
	g++ -Wall -fopenmp -std=c++14 main.cpp -o app

seq:
	g++ -Wall -std=c++14 main.cpp -o app

run:	all
	./app small-2-009.net

cmp:	run
	diff small-2-009.rcb expected-small-2-009.rcb