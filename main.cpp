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
#include <TS.h>
#include <GA.h>
#include <ACO.h>
#include <PSO.h>
#include <Gnuplot.h>
#include <lib.h> 

using namespace std;

int main(int argc, char** argv)
{

    int name_algo       = atoi(argv[1]);
    int num_bit         ;
    int num_evaluation  ;
    int num_run         ;
    int name_function   ;
    clock_t begin       ;
    if(name_algo == 10)     goto PLOT; 
    else
    {
        num_bit         = atoi(argv[2]);
        num_evaluation  = atoi(argv[3]);
        num_run         = atoi(argv[4]);
        name_function   = atoi(argv[5]);
    } 

    if(name_function == 2 && (num_bit > 15))    
    {
        cout << "---ALERT---" << endl;
        cout << "Num_bit is too long." << endl;
        exit(0);
    }

    PLOT:
    begin = clock();

    // switch method
    // switch (name_algo)
    // {
    //     case 0:
    //     {
    //         testfile testfile(name_algo, num_bit);
    //         testfile.main();
    //         break;
    //     }
    //     case 1:
    //     {
    //         ES ES(name_algo, num_bit, num_evaluation, num_run, name_function);
    //         ES.main();
    //         break;
    //     }
    //     case 2:
    //     {
    //         string way_method = argv[6];
    //         HC HC(name_algo, num_bit, num_evaluation, num_run, name_function, way_method);
    //         HC.main();
    //         break;
    //     }
    //     case 3:
    //     {
    //         string way_method = argv[6];
    //         SA SA(name_algo, num_bit, num_evaluation, num_run, name_function, way_method);
    //         SA.main();
    //         break;
    //     }
    //     case 4:
    //     {
    //         string way_method = argv[6];
    //         TS TS(name_algo, num_bit, num_evaluation, num_run, name_function, way_method);
    //         TS.main();
    //         break;
    //     }
    //     case 5:
    //     {
    //         int num_population = atoi(argv[6]);
    //         string way_selection = argv[7];
    //         string way_crossover = argv[8];
    //         double crossover_rate = atof(argv[9]);
    //         double mutation_rate = atof(argv[10]);
    //         GA GA(name_algo, num_bit, num_evaluation, num_run, name_function, num_population, way_selection, way_crossover, crossover_rate, mutation_rate);
    //         GA.main();
    //         break;
    //     }
    //     case 6:
    //     {   
                // int num_population = atoi(argv[6]);
                // double alpha       = atof(argv[7]);
                // double beta        = atof(argv[8]);
                // double rho         = atof(argv[9]);
                // double q           = atof(argv[10]);
                // ACO ACO(name_algo, num_bit, num_evaluation, num_run, name_function, num_population, alpha, beta, rho, q);
    //         ACO.main();
    //     }
    //     case 10:
    //     {
    //         name_function   = atoi(argv[2]);
    //         Gnuplot Gnuplot(name_algo, name_function);
    //         Gnuplot.main();
    //         break;
    //     }   
    //     default:
    //     {
    //         cout << "##########   Please check the name of method.   ##########" << endl;
    //         break;
    //     }
    // }

    // if method
    if(name_algo == 0)
    {   
        testfile testfile(name_algo, num_bit);
        testfile.main();
    }
    else if(name_algo == 1)
    {   
        ES ES(name_algo, num_bit, num_evaluation, num_run, name_function);
        ES.main();
    }
    else if(name_algo == 2)
    {   
        string way_method = argv[6];
        HC HC(name_algo, num_bit, num_evaluation, num_run, name_function, way_method);
        HC.main();
    }
    else if(name_algo == 3)
    {   
        string way_method = argv[6];
        SA SA(name_algo, num_bit, num_evaluation, num_run, name_function, way_method);
        SA.main();
    }
    else if(name_algo == 4)
    {   
        string way_method = argv[6];
        TS TS(name_algo, num_bit, num_evaluation, num_run, name_function, way_method);
        TS.main();
    }
    else if(name_algo == 5)
    {   
        int num_population = atoi(argv[6]);
        string way_selection  = argv[7];
        string way_crossover  = argv[8];
        double crossover_rate = atof(argv[9]);
        double mutation_rate  = atof(argv[10]);
        GA GA(name_algo, num_bit, num_evaluation, num_run, name_function, num_population, way_selection, way_crossover, crossover_rate, mutation_rate);
        GA.main();
    }
    else if(name_algo == 6)
    {   
        int num_population = atoi(argv[6]);
        double alpha       = atof(argv[7]);
        double beta        = atof(argv[8]);
        double rho         = atof(argv[9]);
        double q           = atof(argv[10]);
        string dataset     = argv[11];
        ACO ACO(name_algo, num_bit, num_evaluation, num_run, name_function, num_population, alpha, beta, rho, q, dataset);
        ACO.main();
    }
    else if(name_algo == 7)
    {   
        int num_population = atoi(argv[6]);
        double w           = atof(argv[7]);
        double c1          = atof(argv[8]);
        double c2          = atof(argv[9]);
        int dimension      = atof(argv[10]);
        PSO PSO(name_algo, num_bit, num_evaluation, num_run, name_function, num_population, w, c1, c2, dimension);
        PSO.main();
    }
    else if(name_algo == 10)
    {   
        name_function   = atoi(argv[2]);
        Gnuplot Gnuplot(name_algo, name_function);
        Gnuplot.main();
    }
    else    cout << "##########   Please check the name of method.   ##########" << endl;

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "---------------------"                 << endl;
    cout << elapsed_secs << " sec." << endl;
    cout << "DONE."                                 << endl;

}