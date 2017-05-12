#include <omp.h>
#include <vector>
#include <limits.h>
#include <stdint.h>
#include <math.h>

#include <iostream>

#include "utils.h"
#include "mpi.h"

void sieveOpenMP(uint64_t n, int nThreads)
{
	double time;

	time = -omp_get_wtime();

	uint64_t size = n / 2 + n % 2;
	uint32_t max_seed_index = (uint32_t)sqrt(n) / 2;
	std::vector<bool> marked(size);
		
	for (uint32_t i = 0; i < max_seed_index; ++i) {
		if (!marked[i]) 
		{
			uint64_t value = 2 * i + 3;
			#pragma omp parallel for num_threads(nThreads)
			for (uint64_t j = value * value; j <= n; j += 2 * value) 
			{
				marked[((unsigned)j - 3) / 2] = true;
			}
		}
	}	

	time += omp_get_wtime();

	printProcessingTime(time);
	printPrimesOptimized(marked, size, 5);
}

void seqSieveOptimized(uint64_t n)
{
	double time;
	time = -omp_get_wtime();
	
	uint64_t size = n / 2 + n % 2;	
	uint32_t max_seed_index = (uint32_t)sqrt(n) / 2;
	std::vector<bool> marked(size);

	for (uint32_t i = 0; i < max_seed_index; ++i) {
		if (!marked[i]) 
		{
			uint64_t value = 2 * i + 3;
			for (uint64_t j = value * value; j <= n; j += 2 * value) 
			{
				marked[((unsigned)j - 3) / 2] = 1;
			}
		}
	}

	time += omp_get_wtime();

	printProcessingTime(time);
	printPrimesOptimized(marked, size, 5);
}

void seqSieve(uint64_t n)
{
	double time;

	time = -omp_get_wtime();

	uint64_t size = n;
	uint32_t max_seed_index = (uint32_t)sqrt(n);
	std::vector<bool> marked(size);

	for (uint32_t i = 2; i < max_seed_index; ++i) {
		if (!marked[i]) 
		{
			for (uint64_t j = i * i; j <= n; j += i) 
			{
				marked[(unsigned)j] = 1;
			}
		}
	}

	time += omp_get_wtime();

	printProcessingTime(time);
	printPrimesNormal(marked, size, 5);
}
