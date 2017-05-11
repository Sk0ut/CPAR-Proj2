#include <stdio.h>
#include <mpi.h>
#include <iostream>


using namespace std;

void openMPISieve(uint64_t n) {
    int rank, size;
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);    

    cout << "Status: size=" << size << " rank=" << rank << endl;
}


int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	uint64_t n;
	sscanf(argv[1], "%lu", &n);

	openMPISieve(n);

	MPI_Finalize();
	return 0;
}
