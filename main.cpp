#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#include "sieve.h"

#define MAX_BOUND 32
#define MIN_BOUND 25

using namespace std;

typedef void (* seqSieveFunc)(uint64_t n);

uint64_t askForBoundLimit() {
    uint64_t n;

    cout << "Insert search upper bound: ";
    cin >> n;

    if (n < 2) 
    {
        cout << "The upper bound limit must be greater than 2.\n";
        return -1;
    }

    return n;
}

int askForThreadNumber() {

    int i;
    int nthreads = omp_get_max_threads();
	int ncpus = omp_get_num_procs();

    cout << nthreads << " Thread(s) available(s).\n";
    cout << ncpus << " CPU(s) available(s).\n\n";

    cout << "Insert the number of threads: ";
    cin >> i;

    if (i < 0 || i > nthreads) 
    {
        cout << "Chosen value is outside the range.\n";
        return -1;
    }

    return i;

}

void seqMenu(seqSieveFunc sieveCall, string type)
{     
    int opt;
    uint64_t n;  
    
    do {
        cout << "\nSequencial Mode - " << type << ":\n";
        cout << "\t1. Perfomance Test Mode\n";
        cout << "\t2. Manual Test\n";

        cout << "\n\t0. Cancel\n";
    
        cout << "\nChose an option: ";
        
        cin >> opt;

        switch(opt) {
            case 0: 
                return;
            case 1: 
                for (int i = MIN_BOUND; i <= MAX_BOUND; i++)
                {                    
                    sieveCall(pow(2, i));
                }
                break;
            case 2:      
                n = askForBoundLimit();
                if (n == -1) {
                    break;
                }
                sieveCall(n);
                break;
            default:
                cout << "Invalide Option!\n";
                break;
        
        }    
    } while(true);
}

void openMPMenu()
{     
    int opt, nThreads;  
    uint64_t n;
    
    do {
        cout << "\nParallel Mode - OpenMP:\n";

        cout << "\t1. Perfomance Test Mode\n";
        cout << "\t2. Manual Test\n";

        cout << "\n\t0. Cancel\n";
    
        cout << "\nChose an option: ";
        
        cin >> opt;

        switch(opt) {
            case 0: 
                return;
            case 1:                 
                nThreads = askForThreadNumber();
                if (nThreads == -1) {
                    break;
                }
                for (int i = MIN_BOUND; i <= MAX_BOUND; i++)
                {                    
                    sieveOpenMP(pow(2, i), nThreads);
                }
                break;
            case 2: 
                n = askForBoundLimit();
                if (n == -1) {
                    break;
                }
                nThreads = askForThreadNumber();
                if (nThreads == -1) {
                    break;
                }
                sieveOpenMP(n, nThreads);
                break;
            default:
                cout << "Invalide Option!\n";
                break;
        
        }    
    } while(true);
}

void openMPIMenu()
{     
    int res;
    res = system("mpirun -np 4 mpisieve 2");

    if (res != 0) {
        cout << "[warn] MPI program returned " << res << ".\n";
    }
}

void mainMenu() 
{   
    int opt;
        
    do {
        cout << "\nSequencial Mode:\n";
            cout << "\t1. Normal\n";
            cout << "\t2. Optimized\n";

        cout << "\nParallel Mode:\n";
            cout << "\t3. OpenMP \n";
            cout << "\t4. OpenMPI \n";
            cout << "\t5. OpenMP + OpenMPI \n";

        cout << "\t0. Exit \n";

        cout << "\nChose an option: ";

        cin >> opt;

        switch(opt) {
            case 0: 
                return;
            case 1: 
                seqMenu(seqSieve, "Normal");
                break;
            case 2:
                seqMenu(seqSieveOptimized, "Optimized");
                break;
            case 3:
                openMPMenu();
                break;
            case 4:
                openMPIMenu();
                break;
            case 5:
                break;
            default:
                cout << "Invalide Option!\n";
                break;        
        }
    } while(true);
}


int main(int argc, char *argv[])
{    
    mainMenu();	
	return 0;
}
