#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <sys/file.h>
#include <sys/stat.h> 
#include <sys/types.h> 

#include <testfile.h>
#include <ES.h>
#include <HC.h>
#include <SA.h>
#include <Gnuplot.h>
#include <lib.h> 

using namespace std;

int main(int argc, char** argv)
{

    int name_algo       = atoi(argv[1]);
    int num_bit         = atoi(argv[2]);
    int num_evaluation  = atoi(argv[3]);
    int num_run         = atoi(argv[4]);

    clock_t begin = clock();

    if(name_algo == 0)
    {   
        testfile testfile(name_algo, num_bit);
        testfile.main();
    }
    else if(name_algo == 1)
    {   
        ES ES(name_algo, num_bit, num_evaluation, num_run);
        ES.onemax();
    }
    else if(name_algo == 2)
    {   
        HC HC(name_algo, num_bit, num_evaluation, num_run);
        HC.onemax();
    }
    else if(name_algo == 3)
    {   
        SA SA(name_algo, num_bit, num_evaluation, num_run);
        // SA.onemax();
        SA.deception();
    }
    else if(name_algo == 10)
    {   
        Gnuplot Gnuplot(name_algo);
        Gnuplot.main();
    }
    else    cout << "##########   Please check the name of method.   ##########" << endl;

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "---------------------"                 << endl;
    cout << elapsed_secs << " sec." << endl;
    cout << "DONE."                                 << endl;

}