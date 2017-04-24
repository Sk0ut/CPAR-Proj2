#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "mpi.h"

int main( int argc, char **argv)
{
    uint32_t n;

    printf("N? ");
    scanf("%d", &n);

    uint32_t max_seed = sqrt(n);
    
    uint32_t size = n / 2;
    uint32_t max_seed_index = max_seed / 2;
    uint8_t marked[size - 1 + n%2]; // only consider odd numbers starting on 3
    memset(marked, 0, size);

    for (uint32_t i = 0; i < max_seed_index; ++i) {
        if (!marked[i]) {
            uint32_t value = 2 * i + 3;
            for (uint32_t j = 3 * value; j <= n; j += 2*value) {
                marked[(j-3) / 2] = 1;
            }
        }
    }

    printf("Prime numbers till %d:", n);
    for (uint32_t i = 0; i < size; ++i) {
        if (!marked[i]) {
            printf(" %d", 2*i + 3);
        }
    }
    printf("\n");

    return 0;
}
