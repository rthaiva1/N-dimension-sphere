all: histo_seq histo_parallel histo_optimized 4dvector plotgraph

histo_s: histo_seq
	./histo_s 100 10

histo_p: histo_parallel
	./histo_p 100 10 4

histo_o: histo_optimized
	./histo_o 100 10

4d: 4dvector
	./4d

plot: plotgraph
		./plot 100

histo_seq:
	g++ -Wall -Wextra -pedantic -o histo_s histo_seq.cpp

histo_parallel:
	g++ -fopenmp -Wall -Wextra -pedantic -o histo_p histo_parallel.cpp

histo_optimized:
	g++ -fopenmp -Wall -Wextra -pedantic -o histo_o histo_optimized.cpp

4dvector:
	g++ -fopenmp -Wall -Wextra -pedantic -o 4d 4dvector.cpp -march=sandybridge

plotgraph:
	g++ -fopenmp -Wall -Wextra -pedantic -o plot plotgraph.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7
