# Assignment-2
CS 447/547 2019 S: Assignment 2
http://www.cs.binghamton.edu/~kchiu/cs547/prog/2/

Name: Rosh Thaivalappil
Email id: rthaiva1@binghamton.edu

Type make and executable file name to execute with default values
Part1:-
histo_s : sequential execution
histo_p : parallel execution
histo_o : inverse transformation
plot : plotting in graph

Part2:-
4d :- part 2 execution file

Type make to compile all code
Compile using:-
histo_s:- g++ -Wall -Wextra -pedantic -o histo_s histo_seq.cpp
histo_p:- g++ -fopenmp -Wall -Wextra -pedantic -o histo_p histo_parallel.cpp
histo_o:- g++ -fopenmp -Wall -Wextra -pedantic -o histo_o histo_optimized.cpp
plot:- g++ -fopenmp -Wall -Wextra -pedantic -o plot plotgraph.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7
4d:-  g++ -fopenmp -Wall -Wextra -pedantic -o 4d 4dvector.cpp -march=sandybridge

Note:-
Input:-number of points, the dimension to be printed(only 1 dimension at a time) and threads as input.
Output:-no. of points printed,{interval , number of points in that interval}
