#ifndef __ES_H_INCLUDED__
#define __ES_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class ES
{
  public:
    ES(
        int algo,
        int population
    );
    ~ES() {}
    
    void algorithm();
  
  private://parameters
  
    int algo;
    int population;

    v1i pop_vec;
    int c_one;  // how many one in the vector
    int n_best;

    // measurement
    double searching_secs;

  private://functions

};
#endif