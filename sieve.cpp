#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <omp.h>

using namespace std;

//	#include "mpi.h"

void printProcessingTime(double timeMs) 
{
	char st[100];

	sprintf(st, "Time: %3.3f seconds\n", timeMs);	
	printf("%s", st);
}

void sequentialSieveParallel(uint64_t n)
{       
  double Time1, Time2;

  Time1 = omp_get_wtime();

  uint32_t size = n / 2 + n % 2;
  uint32_t max_seed_index = sqrt(n) / 2;  
  vector<bool> marked(size);

  for (uint32_t i = 0; i < max_seed_index ; ++i) {
    if (!marked[i]) {
      uint32_t value = 2 * i + 3;      
      uint32_t maxFactor = (uint32_t) n / value;
      #pragma omp parallel for num_threads(4)
      for (uint64_t j = value ; j <= maxFactor; j += 2) {
          marked[(j*value-3) / 2] = 1;
      }
    }
  }

  Time2 = omp_get_wtime();	
	double processingTime = Time2 - Time1;

  printProcessingTime(processingTime);
  
  int count = 1;

  printf("Prime numbers till %ld:", n);
	printf(" %d", 2);
  for (uint32_t i = 0; i < size - 1; ++i) {
    if (!marked[i]) {
      printf(" %u", 2*i + 3);
      ++count;
    }
  }
  printf("\n");
  printf("Total Primes: %d\n",count);
}

void sequentialSieve(uint64_t n)
{       
  double Time1, Time2;

  Time1 = omp_get_wtime();

  uint32_t size = n / 2 + n % 2;
  uint32_t max_seed_index = sqrt(n) / 2;  
  vector<bool> marked(size);

  for (uint32_t i = 0; i < max_seed_index ; ++i) {
    if (!marked[i]) {
      uint32_t value = 2 * i + 3;
      for (uint64_t j = value * value; j <= n; j += 2*value) {
          marked[(j-3) / 2] = 1;
      }
    }
  }

  Time2 = omp_get_wtime();	
	double processingTime = Time2 - Time1;

  printProcessingTime(processingTime);

  /*printf("Prime numbers till %ld:", n);
	printf(" %d", 2);
  for (uint32_t i = 0; i < size - 1; ++i) {
    if (!marked[i]) {
      printf(" %u", 2*i + 3);
    }
  }
  printf("\n");*/
}

void sequentialSieve2(uint64_t n)
{
	double Time1, Time2;

	Time1 = omp_get_wtime();

	uint32_t size = n;
	uint32_t max_seed_index = sqrt(n);
	vector<bool> marked(size);

	for (uint32_t i = 0; i < max_seed_index; ++i) {
		if (!marked[i]) {
			uint32_t value = i + 2;
			for (uint64_t j = value * value; j <= n; j += value) {
				marked[(j - 2)] = 1;
			}
		}
	}

	Time2 = omp_get_wtime();
	double processingTime = Time2 - Time1;

	printProcessingTime(processingTime);

	printf("Prime numbers till %ld:", n);
	for (uint32_t i = 0; i < size - 1; ++i) {
		if (!marked[i]) {
			printf(" %u", i + 2);
		}
	}
	printf("\n");
}


int main (int argc, char *argv[])
{
	if (argc != 2) 
	{
		printf("Usage: %s <n>\n", argv[0]);
	}
	else
	{
		uint32_t n = atoi(argv[1]);
		if (n < 2)
		{
			printf("n must be grater or equal than 2.");
		}
		else
		{
			printf("optimized: ");
			sequentialSieve(n);
			printf("normal: ");
			sequentialSieve2(n);
		}
	}
	return 0;
}
