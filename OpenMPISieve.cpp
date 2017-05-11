#include <stdio.h>
#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	uint32_t n;
	sscanf(argv[1], "%u", &n);

	//  openMPISieve(n);

	MPI_Finalize();
	return 0;
}
