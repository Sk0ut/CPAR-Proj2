CXX=g++
MPIXX=mpic++ -std=c++11
RM=rm -f

all: sieve

sieve:
	$(MPIXX) OpenMPISieve.cpp utils.cpp -o mpisieve
	$(CXX) -fopenmp main.cpp sieve.cpp utils.cpp -O2 -o sieve	
clean:
	$(RM) sieve mpisieve
