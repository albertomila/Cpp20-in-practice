#pragma once
#include "stdafx.h"
using namespace std;

struct Max_Data
{
	int pos_;
	Max_Data() : pos_(0){}
	Max_Data(int pos) : pos_(pos){}
};

struct Max_Predicate
{
	Max_Predicate() {}
	bool operator()(const Max_Data& t1,const Max_Data& t2)
	{
		return t1.pos_  < t2.pos_;
	}
};


BEGIN_TEST(Max)
  cout << "max(1,2)==" << max(1,2) << endl;
  cout << "max(2,1)==" << max(2,1) << endl;
  cout << "max('a','z')==" << max('a','z') << endl;
  cout << "max(3.14,2.72)==" << max(3.14,2.72) << endl;

  Max_Data t = max(Max_Data(0), Max_Data(8), Max_Predicate());
  t = max(Max_Data(8), Max_Data(0), Max_Predicate());

END_TEST()