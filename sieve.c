#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
//	#include "mpi.h"

void sequentialSieve(uint64_t n)
{       
  uint32_t size = n / 2 + n % 2;
  uint32_t max_seed_index = sqrt(n) / 2;
  uint8_t marked[size]; // only consider odd numbers starting on 3
  memset(marked, 0, size);

  for (uint32_t i = 0; i < max_seed_index ; ++i) {
    if (!marked[i]) {
      uint32_t value = 2 * i + 3;
      for (uint64_t j = value * value; j <= n; j += 2*value) {
          marked[(j-3) / 2] = 1;
      }
    }
  }

  printf("Prime numbers till %ld:", n);
	printf(" %d", 2);
  for (uint32_t i = 0; i < size - 1; ++i) {
    if (!marked[i]) {
      printf(" %ld", 2*i + 3);
    }
  }
  printf("\n");
}


void sequentialSieveMemorySaving(uint64_t n)
{ 
	uint32_t elemSize = sizeof(uint32_t)*8;   
	uint32_t totalBits = ceil(n / 2);
  uint32_t size = ceil(totalBits / (float)elemSize);

  uint32_t max_seed_bit_index = sqrt(n) / 2;
	uint32_t max_seed_index = ceil(max_seed_bit_index / (float)elemSize);

  uint32_t marked[size]; // only consider odd numbers starting on 3
  memset(marked, 0, size*sizeof(uint32_t));

  for (uint32_t i = 0; i < max_seed_index ; ++i) {
		uint32_t bit_max_index = elemSize;
		if (i + 1 >= max_seed_index) {
			bit_max_index = max_seed_bit_index - elemSize * i;
		}
		for (uint32_t k = 0; k < bit_max_index; k++) {
			uint32_t bit = ((marked[i] & ( 1 << k )) >> k);
			if (!bit) {			
				uint32_t value = 2 * (elemSize * i + k) + 3;	
			  for (uint64_t j = value * value; j <= n; j += 2*value) {					
					uint32_t element = (j-3) / 2;
					uint32_t index = element / elemSize;
					uint32_t bit_index = element % elemSize;
			    marked[index] |= 1 << bit_index;
			  }
			}
		}	
  }

	int totalPrimes = 1;

  printf("Prime numbers till %ld:\n", n);
	printf(" %d", 2);
  for (uint32_t i = 0; i < size; ++i) {
		uint32_t bit_max_index = 32;
		if (i + 1 >= size) {
			bit_max_index = totalBits - 32 * i - 1;
		}
		for(uint32_t k = 0; k < bit_max_index; k++) {
			uint32_t bit = ((marked[i] & ( 1 << k )) >> k);
			if (!bit) {
		    printf(" %d", 2*(k + i*32) + 3);
				totalPrimes++;
		  }			
		}   
  }
  printf("\n");

	printf("Total Primes: %d\n", totalPrimes);
}


int main (int argc, char *argv[])
{
	if (argc != 2) 
	{
		printf("Usage: %s <n>\n", argv[0]);
	}
	else
	{
		int n = atoi(argv[1]);
		if (n < 2)
		{
			printf("n must be grater or equal than 2.");
		}
		else
		{
			sequentialSieveMemorySaving(n);
		}
	}
	return 0;
}
