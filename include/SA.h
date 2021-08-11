#ifndef __SA_H_INCLUDED__
#define __SA_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class SA : public Algo
{
  public:
	SA(
		int name_algo,
		int num_bit,
		int num_evaluation,
		int num_run,
		int function,
		string way_method);
	~SA() {}

	void main();

  private: //parameters
	double initial_temperature;

  private: //functions
	inline void transition(v1i &temp_solution_vec);
};
#endif