CXX=g++
RM=rm -f

all: sieve

sieve:
	$(CXX) -fopenmp sieve.cpp -O2 -o sieve

clean:
	$(RM) sieve
