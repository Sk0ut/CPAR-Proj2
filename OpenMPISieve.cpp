#include <stdio.h>
#include <mpi.h>
#include <iostream>

#include "utils.h"

using namespace std;

void openMPISieve(uint64_t n) {
    int rank, size;
    double time = 0;
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);    

    cout << "Status: size=" << size << " rank=" << rank << endl;

    if(rank == 0) {
		time = -MPI_Wtime();
	}

    // Algoritmo AKI

    if(rank == 0) {
		time += MPI_Wtime();
        printProcessingTime(time); 
	}
}


int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	uint64_t n;
	sscanf(argv[1], "%lu", &n);

	openMPISieve(n);

	MPI_Finalize();
	return 0;
}
