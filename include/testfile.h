#ifndef __TESTFILE_H_INCLUDED__
#define __TESTFILE_H_INCLUDED__

#include <iostream>
#include "lib.h"

using namespace std;

class testfile
{
  public:
	testfile(
		int name_algo,
		int num_bit
	);
	~testfile() {}
	
	void main();
  
  private://parameters
  
	int name_algo;
	int num_bit;

  private://functions

};
#endif