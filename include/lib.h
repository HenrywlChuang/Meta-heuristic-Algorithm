#ifndef __LIB_H_INCLUDED__
#define __LIB_H_INCLUDED__

#include <iostream>
#include <iomanip>
#include <vector>
#include <string.h>
#include <math.h>
#include <fstream>
#include <float.h>
#include <algorithm>
#include <time.h>
#include <numeric>
#include <dirent.h>

using namespace std;

// type def
typedef vector<int> v1i    ;
typedef vector<v1i> v2i    ;
typedef vector<v2i> v3i    ;
typedef vector<v3i> v4i    ;
typedef vector<v4i> v5i    ;
typedef vector<v5i> v6i    ;
typedef vector<double> v1d ;
typedef vector<v1d> v2d    ;
typedef vector<v2d> v3d    ;
typedef vector<v3d> v4d    ;
typedef vector<bool> v1b   ;
typedef vector<string> v1s ;
typedef vector<v1s> v2s    ;

// global functions
void see_solution_v1i_vec(const v1i& solution_vec);
void see_solution_v1d_vec(const v1d& solution_vec);
void see_solution_v2i_vec(const v2i& solution_vec);
void evaluation_deception(double& current_fitness, const v1i& temp_solution_vec);
void evaluation_onemax(double& current_fitness, const v1i& temp_solution_vec);
void evaluation(double& current_fitness, const v1i& solution_vec, const int& name_algo);
void evaluation_population(v1d& current_fitness_pop, const v2i& solution_vec_pop, const int& name_algo);
void write_best_file(const string& name_algo, const double& global_best);
void initialization_population(v2i& solution_vec_pop, const int& num_bit, const int& num_population);
void initialization(v1i& solution_vec, const int& num_bit);
void determination(double& current_fitness, double& latest_best, const v1i& temp_solution_vec, v1i& solution_vec);
void write_average_file(const string& name_algo, const v1d& average_best, const int& num_run, const int& name_function);
void save_global_best(double& global_best, double& latest_best);
int binary_to_decimal(const v1i& temp_solution_vec);
void local_best_population(const v1d& current_fitness_pop, double& global_best);

// global class
class Algo
{
  public:
	Algo(int name_algo, int num_bit, int num_evaluation, int num_run, int name_function);
	~Algo(){}

	int name_algo;
	int num_bit;
	int num_evaluation;
	int num_run;
	int name_function;

	v1i solution_vec;
	v2i solution_vec_pop;	// save every solution into a vector
	double current_fitness;  // how many one in the vector
	v1d current_fitness_pop;	// save every current fitness into a vector
	double global_best;
	string way_method;
	v1d average_best;

	// measurement
	double searching_secs;

  protected:

  private:

};

#endif