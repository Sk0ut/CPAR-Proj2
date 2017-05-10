#include <iostream>
#include <vector>

using namespace std;

void printProcessingTime(double timeMs)
{
	char st[100];

	sprintf_s(st, "Time: %3.3f seconds\n", timeMs);
	cout << st;
}

void printPrimesOptimized(vector<bool> &marked, uint32_t size, int printNum = INT_MAX)
{
	cout << "Prime numbers: \n";
	
	int count = 0;
	
	for (uint32_t i = size - 2; i-- > 0;) {
		if (!marked[i])
		{
			if (++count <= printNum)
			{
				cout << 2 * i + 3 << " ";
			}
		}
	}
	if (++count <= printNum) {
		cout << " 2";
	}

	cout << "\nTotal Primes: " << count << endl;
}

void printPrimesNormal(vector<bool> &marked, uint32_t size, int printNum = INT_MAX)
{
	cout << "Prime numbers: \n";

	int count = 0;

	for (uint32_t i = size - 2; i-- > 0;) {
		if (!marked[i]) {
			if (++count <= printNum)
			{
				cout << i + 2 << " ";
			}
		}
	}

	cout << "\nTotal Primes: " << count << endl;
}