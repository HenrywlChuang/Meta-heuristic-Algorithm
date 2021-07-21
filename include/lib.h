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
void see_population_vec(v1i population_vec);
void evaluation(int& current_one, v1i population_vec);
void write_best_file(string name_algo, int global_best);
void initialization(v1i& population_vec, int num_bit);
void determination(int& current_one, int& global_best, v1i temp_population_vec, v1i& population_vec);
void write_average_file(string name_algo, v1d average_best, int num_run);

// global class

#endif