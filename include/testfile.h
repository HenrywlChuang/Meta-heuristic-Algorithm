#ifndef __TESTFILE_H_INCLUDED__
#define __TESTFILE_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class testfile
{
  public:
    testfile(
        int algo,
        int population
    );
    ~testfile() {}
    
    void algorithm();
  
  private://parameters
  
    int algo;
    int population;

  private://functions

};
#endif