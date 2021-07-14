#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <sys/file.h>
#include <sys/stat.h> 
#include <sys/types.h> 

#include <testfile.h>
#include <ES.h>
#include <lib.h> 

using namespace std;

int main(int argc, char** argv)
{

    int algo       = atoi(argv[1]);
    int population = atoi(argv[2]);

    clock_t begin = clock();

    if(algo == 0)
    {   
        testfile testfile(algo, population);
        testfile.algorithm();
    }
    if(algo == 1)
    {   
        ES ES(algo, population);
        ES.algorithm();
    }

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "---------------------"                 << endl;
    cout << elapsed_secs << " sec." << endl;
    cout << "DONE."                                 << endl;

}