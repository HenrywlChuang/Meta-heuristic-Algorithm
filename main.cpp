#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <sys/file.h>
#include <sys/stat.h> 
#include <sys/types.h> 

#include <testfile.h>
#include <lib.h> 

using namespace std;

int main(int argc, char** argv)
{

    int algo       = atoi(argv[1]);
    int population = atoi(argv[2]);

    if(algo == 0)
    {   
        testfile testfile(algo, population);
        testfile.algorithm();
    }

    cout << "---------------------"                 << endl;
    cout << "DONE."                                 << endl;

}