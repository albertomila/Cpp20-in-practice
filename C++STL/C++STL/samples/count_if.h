#pragma once
#include "stdafx.h"
using namespace std;

struct CountIf_Predicate_IsOdd
{
	bool operator()(int value)
	{
		return ((value % 2) == 1);
	}
};

struct CountIf_Data
{
	int pos_;
	CountIf_Data() : pos_(0){}
	CountIf_Data(int pos) : pos_(pos){}
};

struct CountIf_Predicate
{
	CountIf_Predicate(){}
	bool operator()(const CountIf_Data& t)
	{
		return t.pos_ == 0;
	}
};

BEGIN_TEST(CountIf)
  int mycount;

  vector<int> myvector;
  for (int i=1; i<10; i++) myvector.push_back(i); // myvector: 1 2 3 4 5 6 7 8 9

  mycount = (int) count_if (myvector.begin(), myvector.end(), CountIf_Predicate_IsOdd());
  cout << "myvector contains " << mycount  << " odd values.\n";

  
  vector<CountIf_Data> origin;
  origin.push_back(CountIf_Data(0));
  origin.push_back(CountIf_Data(1));
  origin.push_back(CountIf_Data(2));
  origin.push_back(CountIf_Data(3));
  origin.push_back(CountIf_Data(4));
  origin.push_back(CountIf_Data(5));

  int x = count_if (origin.begin(), origin.end(), CountIf_Predicate());

END_TEST()