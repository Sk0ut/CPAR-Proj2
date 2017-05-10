#ifndef SIEVE_H
#define SIEVE_H

#include <stdint.h>

void sieveOpenMP(uint32_t n, int nThreads);
void seqSieveOptimized(uint32_t n);
void seqSieve(uint32_t n);

#endif
