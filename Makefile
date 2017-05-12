CXX=g++ -std=c++11
MPIXX=mpic++ -std=c++11
RM=rm -f

all: sieve

sieve:
	$(MPIXX) OpenMPISieveV2.cpp utils.cpp -o mpisieve
	$(MPIXX) OpenMPI_OMPSieve.cpp utils.cpp -o mpimpsieve
	$(CXX) -fopenmp main.cpp sieve.cpp utils.cpp -O2 -o sieve	
clean:	
	$(RM) mpisieve
	$(RM) mpimpsieve	
	$(RM) sieve
