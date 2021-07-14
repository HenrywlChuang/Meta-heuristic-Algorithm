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
void see_popvec(v1i pop_vec);
void evaluation(int& c_one, v1i pop_vec);
void w_file(string algo, int best);

// global class

#endif