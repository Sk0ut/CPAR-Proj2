#include <stdio.h>
#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>

#include <unistd.h>
#include <time.h>

#include "utils.h"

using namespace std;

void openMPISieve(uint64_t n) {
    int rank, size;
    double time = 0;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    uint32_t blockBaseValue = rank * n / size;
    int blockSize = n / size + n % size;    
	uint32_t max_seed_index = (uint32_t)sqrt(n);

    vector<bool> marked(blockSize);
    
    MPI_Barrier(MPI_COMM_WORLD);

    if(rank == 0) {
		time = -MPI_Wtime();
	}

    for (uint32_t i = 2; i < max_seed_index; ) 
    {
        uint32_t startValue = i*i;

        if (startValue < blockBaseValue) 
        {
            if (blockBaseValue % i != 0) 
            {
                startValue = blockBaseValue + (i - (blockBaseValue % i));
            }
            else {
                startValue = blockBaseValue;
            }
		}
        for (uint64_t j = startValue; j < blockBaseValue + blockSize; j += i) 
		{
			marked[(unsigned int)j - blockBaseValue] = true;
		}

        if (rank == 0) {
			do {
				i++;
			} while (marked[i] && i < max_seed_index);
		}

		MPI_Bcast(&i, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    }

    int count = 0;

    for (uint64_t i = blockSize; i-- > 0; ) {
        if (!marked[i]) 
        {
            if(count < 1)
            {
                cout << " " << i + blockBaseValue;               
            }
            ++count;
        }      
    }    
    
    int primes;

	MPI_Reduce(&count, &primes, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	  
    if(rank == 0) {
        cout << "Total Primes: " << primes - 2 << endl;
		time += MPI_Wtime();
        printProcessingTime(time); 
	}
}


int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
    srand( time(NULL));
	uint64_t n;
	sscanf(argv[1], "%lu", &n);

	openMPISieve(n);

	MPI_Finalize();
	return 0;
}
