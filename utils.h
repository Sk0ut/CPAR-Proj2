#ifndef UTILS_H
#define UTILS_H

#include <vector>

void printProcessingTime(double timeMs);
void printPrimesOptimized(std::vector<bool> &marked, uint32_t size, int printNum = INT_MAX);
void printPrimesNormal(std::vector<bool> &marked, uint32_t size, int printNum = INT_MAX);

#endif