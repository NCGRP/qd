#CXX = g++-5
CXX = g++
FLAGS = -O3 -Wall


all: main.o qdist.o partdist.o Lmunkres.o Hungarian.o BipartiteGraph.o
	${CXX} ${FLAGS} main.o qdist.o partdist.o Lmunkres.o Hungarian.o BipartiteGraph.o -o qd

main.o: main.cpp main.hpp
	${CXX} ${FLAGS} -c main.cpp

qdist.o: qdist.cpp
	${CXX} ${FLAGS} -c qdist.cpp

partdist.o: partdist.cpp partdist.hpp
	${CXX} ${FLAGS} -c partdist.cpp

Lmunkres.o: Lmunkres.cpp Hungarian.h BipartiteGraph.h
	${CXX} ${FLAGS} -c Lmunkres.cpp

Hungarian.o: Hungarian.cpp Hungarian.h BipartiteGraph.h Matrix.h
	${CXX} ${FLAGS} -c Hungarian.cpp
	
BipartiteGraph.o: BipartiteGraph.cpp BipartiteGraph.h Matrix.h
	${CXX} ${FLAGS} -c BipartiteGraph.cpp

clean:
	rm -rf *.o
