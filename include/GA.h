#ifndef __GA_H_INCLUDED__
#define __GA_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class GA : public Algo
{
  public:
	GA(
		int name_algo,
		int num_bit,
		int num_evaluation,
		int num_run,
		int name_function,
		int num_population,
		string way_selection,
		string way_crossover,
		double crossover_rate,
		double mutation_rate
	);
	~GA() {}
	
	void main();
	int num_population;
	double local_best;
	string way_selection;
	string way_crossover;
	double crossover_rate;
	double mutation_rate;
  
  private://parameters

  private://functions

	inline void selection(const string& way_selection, v2i& temp_solution_vec_pop);
	inline void selection_roulette(v2i& temp_solution_vec_pop);
	inline void selection_tournament(v2i& temp_solution_vec_pop);
	inline void crossover(const string& way_crossover, const v2i& temp_solution_vec_pop);
	inline void crossover_one_point(const v2i& temp_solution_vec_pop);
	inline void mutation();
};
#endif