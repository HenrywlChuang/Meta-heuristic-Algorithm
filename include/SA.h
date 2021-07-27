#ifndef __SA_H_INCLUDED__
#define __SA_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class SA
{
  public:
    SA(
        int name_algo,
        int num_bit,
        int num_evaluation,
        int num_run
    );
    ~SA() {}
    
    void onemax();
    void deception();
  
  private://parameters
  
    int name_algo;
    int num_bit;
    int num_evaluation;
    int num_run;

    v1i solution_vec;
    int current_fitness;  // how many one in the vector
    int global_best;
    string way_method;
    double initial_temperature;

    v1d average_best;

    // measurement
    double searching_secs;

  private://functions

    void transition(v1i& temp_solution_vec);
};
#endif