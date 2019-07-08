#pragma once
#include "stdafx.h"
using namespace std;

struct LowerUpperBound_Data
{
	int pos_;
	LowerUpperBound_Data() : pos_(0){}
	LowerUpperBound_Data(int pos) : pos_(pos){}
	bool operator < (const int pos)
	{
		return pos_ < pos;
	}
};


struct LowerUpperBound_Predicate
{
	LowerUpperBound_Predicate() {}
	bool operator()(const LowerUpperBound_Data& t1,const int& pos)
	{
		return t1.pos_  < pos;
	}
};


BEGIN_TEST(LowerUpperBound)
  int myints[] = {10,20,30,30,20,10,10,20};
  vector<int> v(myints,myints+8);           // 10 20 30 30 20 10 10 20
  vector<int>::iterator low,up;

  sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

  low=lower_bound (v.begin(), v.end(), 20); //          ^
  up= upper_bound (v.begin(), v.end(), 20); //                   ^

  cout << "lower_bound at position " << int(low- v.begin()) << endl;
  cout << "upper_bound at position " << int(up - v.begin()) << endl;


  vector<LowerUpperBound_Data> o;
  o.push_back(LowerUpperBound_Data(0));
  o.push_back(LowerUpperBound_Data(1));
  o.push_back(LowerUpperBound_Data(1));
  o.push_back(LowerUpperBound_Data(1));
  o.push_back(LowerUpperBound_Data(2));
  o.push_back(LowerUpperBound_Data(3));
  o.push_back(LowerUpperBound_Data(4));
  o.push_back(LowerUpperBound_Data(5));
  vector<LowerUpperBound_Data>::iterator lower = lower_bound(o.begin(),o.end(),4);
  lower = lower_bound(o.begin(),o.end(),4,LowerUpperBound_Predicate());

END_TEST()