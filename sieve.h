#ifndef SIEVE_H
#define SIEVE_H

#include <stdint.h>

void sieveOpenMP(uint64_t n, int nThreads);
void seqSieveOptimized(uint64_t n);
void seqSieve(uint64_t n);

#endif
