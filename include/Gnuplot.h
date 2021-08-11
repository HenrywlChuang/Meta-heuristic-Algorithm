#ifndef __Gnuplot_H_INCLUDED__
#define __Gnuplot_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class Gnuplot
{
  public:
	Gnuplot(
		int name_algo,
		int name_function
	);
	~Gnuplot() {}
	
	void main();
  
  private://parameters

	int name_algo;
	int name_function;
	string input_filename;

  private://functions

};
#endif