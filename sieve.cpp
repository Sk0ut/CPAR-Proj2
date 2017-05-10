#include <omp.h>
#include <vector>

#include "utils.h"
//	#include "mpi.h"

void sieveOpenMP(uint32_t n, int nThreads)
{
	double Time1, Time2;

	Time1 = omp_get_wtime();

	uint32_t size = n / 2 + n % 2;
	uint32_t max_seed_index = (uint32_t)sqrt(n) / 2;
	std::vector<bool> marked(size);
		
	for (uint32_t i = 0; i < max_seed_index; ++i) {
		if (!marked[i]) 
		{
			uint32_t value = 2 * i + 3;
			#pragma omp parallel for num_threads(nThreads)
			for (uint64_t j = value * value; j <= n; j += 2 * value) 
			{
				marked[((unsigned int)j - 3) / 2] = true;
			}
		}
	}	

	Time2 = omp_get_wtime();

	printProcessingTime(Time2 - Time1);
	printPrimesOptimized(marked, size, 5);
}

void seqSieveOptimized(uint32_t n)
{
	double Time1, Time2;

	Time1 = omp_get_wtime();
	
	uint32_t size = n / 2 + n % 2;
	
	uint32_t max_seed_index = (uint32_t)sqrt(n) / 2;
	std::vector<bool> marked(size);

	for (uint32_t i = 0; i < max_seed_index; ++i) {
		if (!marked[i]) 
		{
			uint32_t value = 2 * i + 3;
			for (uint64_t j = value * value; j <= n; j += 2 * value) 
			{
				marked[((unsigned int)j - 3) / 2] = 1;
			}
		}
	}

	Time2 = omp_get_wtime();

	printProcessingTime(Time2 - Time1);
	printPrimesOptimized(marked, size, 5);
}

void seqSieve(uint32_t n)
{
	double Time1, Time2;

	Time1 = omp_get_wtime();

	uint32_t size = n;
	uint32_t max_seed_index = (int)sqrt(n);
	std::vector<bool> marked(size);

	for (uint32_t i = 0; i < max_seed_index; ++i) {
		if (!marked[i]) 
		{
			uint32_t value = i + 2;
			for (uint64_t j = value * value; j <= n; j += value) 
			{
				marked[((unsigned int)j - 2)] = 1;
			}
		}
	}

	Time2 = omp_get_wtime();

	printProcessingTime(Time2 - Time1);
	printPrimesNormal(marked, size, 5);
}