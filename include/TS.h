#ifndef __TS_H_INCLUDED__
#define __TS_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class TS : public Algo
{
  public:
	TS(
		int name_algo,
		int num_bit,
		int num_evaluation,
		int num_run,
		int name_function,
		string way_method
	);
	~TS() {}
	
	void main();
  
  private://parameters

	int length_tabulist;
	v2i tabulist_vec;

  private://functions

	inline void transition(v1i& temp_solution_vec);
	inline bool tabulist(const v1i& temp_solution_vec);
};
#endif