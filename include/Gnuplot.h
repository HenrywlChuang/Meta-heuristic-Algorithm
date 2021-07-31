#ifndef __Gnuplot_H_INCLUDED__
#define __Gnuplot_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class Gnuplot
{
  public:
	Gnuplot(
		int name_algo
	);
	~Gnuplot() {}
	
	void main();
  
  private://parameters

	int name_algo;
	string input_filename;

  private://functions

};
#endif