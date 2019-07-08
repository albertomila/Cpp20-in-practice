#pragma once
#include "stdafx.h"
using namespace std;

struct Min_Data
{
	int pos_;
	Min_Data() : pos_(0){}
	Min_Data(int pos) : pos_(pos){}
};

struct Min_Predicate
{
	Min_Predicate() {}
	bool operator()(const Min_Data& t1,const Min_Data& t2)
	{
		return t1.pos_ < t2.pos_;
	}
};


BEGIN_TEST(Min)
  cout << "min(1,2)==" << min(1,2) << endl;
  cout << "min(2,1)==" << min(2,1) << endl;
  cout << "min('a','z')==" << min('a','z') << endl;
  cout << "min(3.14,2.72)==" << min(3.14,2.72) << endl;

  
  Min_Data t = min(Min_Data(0), Min_Data(8), Min_Predicate());
  t = min(Min_Data(8), Min_Data(0), Min_Predicate());

END_TEST()
