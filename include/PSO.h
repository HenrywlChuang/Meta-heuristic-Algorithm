#ifndef __PSO_H_INCLUDED__
#define __PSO_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class PSO : public Algo
{
  public:
	PSO(
		int name_algo,
		int num_bit,
		int num_evaluation,
		int num_run,
		int name_function,
		int num_population,
		double w,
		double c1,
		double c2,
		int dimension
	);
	~PSO() {}
	
	void main();
	int num_population;
	double local_best;
	double w;
	double c1;
	double c2;
	int dimension;

	double upper_bound;
	double lower_bound;
	v2d local_best_particle_pos;
	v1d local_best_particle;
	v1d global_best_particle_pos;
	v2d velocity;
	double real_global_best;



  private://parameters

  private://functions
	inline void initialization_PSO();
	inline void update_best();
	inline void movement();
	inline void check_boundary();

};
#endif