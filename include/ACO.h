#ifndef __ACO_H_INCLUDED__
#define __ACO_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class ACO : public Algo
{
  public:
	ACO(
		int name_algo,
		int num_bit,	// ants
		int num_evaluation,
		int num_run,
		int name_function,
		int num_population,
		double alpha,
		double beta,
		double rho,
		double q,
		string dataset
	);
	~ACO() {}
	
	void main();
	int num_population;
	double local_best;
	double alpha;
	double beta;
	double rho;
	double q;  
	string dataset;

	v2d map_distance;
	v2d coordinate; // read each point from the dataset file
	v2d table_pheromones;	// save pheromones
	v1i local_best_route;
	v1i global_best_route;
	v1i real_global_best_vector;
	double real_global_best;



  private://parameters

  private://functions

	inline void calculate_map();
	inline void initialization_pheromones();
	inline void update_local_pheromones(const v1i& ant_route);
	inline void update_global_pheromones();
	inline void f_local_best_route();	// assign the local best route
	inline void walking(v1i& ant_route);
	inline void plot_the_best_route();

};
#endif