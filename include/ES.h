#ifndef __ES_H_INCLUDED__
#define __ES_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class ES : public Algo
{
  public:
	ES(int name_algo, int num_bit, int num_evaluation, int num_run, int num_function);
	~ES() {}
	
	void main();
  
  private://parameters

  private://functions

	void transition();
};
#endif