#include <stdio.h>
#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <omp.h>

#include "utils.h"

using namespace std;

void openMPISieve(uint64_t n, unsigned nThreads) {
    int rank, size;
    double time = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    uint64_t blockBaseValue = rank * n / size + 1;
    uint32_t blockSize = n / size;    
	uint32_t max_seed_index = (uint32_t)sqrt(n) / 2;

    vector<bool> marked(blockSize / 2);

    MPI_Barrier(MPI_COMM_WORLD);
    
    if(rank == 0) {
		time = -MPI_Wtime();
	}

    for (uint32_t i = 1; i < max_seed_index; ) 
    {
        uint32_t val = i*2 + 1;
        uint64_t startValue = val*val;

        if (startValue < blockBaseValue) 
        {
            if (blockBaseValue % val != 0) 
            {
                startValue = val + (blockBaseValue + val - 1) / (2*val) * (2*val);
            }
            else 
            {
                startValue = blockBaseValue;
            }
		}
        #pragma omp parallel for num_threads(nThreads)
        for (uint64_t j = startValue; j < blockBaseValue + blockSize; j += 2*val) 
		{
			marked[((unsigned int)j - blockBaseValue) / 2] = true;
		}

        if (rank == 0) {
			do {
				i++;
			} while (marked[i] && i < max_seed_index);
		}

		MPI_Bcast(&i, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    }

    if(rank == 0) 
    {        
		time += MPI_Wtime();
        printProcessingTime(time); 
	}

    uint32_t count = 0;

    for (uint32_t i = blockSize / 2; i-- > 0; ) {
        if (!marked[i]) 
        {   
            if(count < 1)
            {
                if (rank == 0 && i == 0)
                {
                    cout << "Highest prime from rank=" << rank << ": " << 2 << endl;
                }
                else
                {
                    cout << "Highest prime from rank=" << rank << ": " << 2*i + !(blockBaseValue % 2) + blockBaseValue << endl;
                }
            }   
            ++count;
        }      
    }    
    
    uint32_t primes;

	MPI_Reduce(&count, &primes, 1, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);	  

    if (rank == 0) 
    {        
        cout << "Total Primes: " << primes << endl;
    }    
}


int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	uint64_t n;
  uint64_t nThreads;
	sscanf(argv[1], "%lu", &n);
  sscanf(argv[1], "%lu", &nThreads);

	openMPISieve(n, nThreads);

	MPI_Finalize();
	return 0;
}
