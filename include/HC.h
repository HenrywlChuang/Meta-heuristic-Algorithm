#ifndef __HC_H_INCLUDED__
#define __HC_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class HC : public Algo
{
  public:
	HC(
		int name_algo,
		int num_bit,
		int num_evaluation,
		int num_run,
		int name_function
	);
	~HC() {}
	
	void main();
  
  private://parameters

  private://functions

	void transition(v1i& temp_solution_vec);
};
#endif