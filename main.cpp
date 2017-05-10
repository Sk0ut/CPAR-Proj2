#include <iostream>
#include <stdio.h>

#include "sieve.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << "<n>\n";
	}
	else
	{		
		uint32_t n;
		sscanf(argv[1], "%u", &n);
		if (n < 2)
		{
			std::cout << "<n> must be grater or equal than 2.\n";
		}
		else
		{
			cout << "optimized: ";
			seqSieveOptimized(n);

			cout << "normal: ";
			seqSieve(n);

			cout << "parallel: ";
			sieveOpenMP(n, 4);
		}
	}

	return 0;
}
