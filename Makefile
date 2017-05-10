CXX=g++
RM=rm -f

all: sieve

sieve:
	$(CXX) -fopenmp main.cpp sieve.cpp utils.cpp -O2 -o sieve

clean:
	$(RM) sieve
