#pragma once
#include "stdafx.h"
using namespace std;

struct ReplaceIf_Data
{
	int pos_;
	ReplaceIf_Data() : pos_(0){}
	ReplaceIf_Data(int pos) : pos_(pos){}
};

struct ReplaceIf_Predicate_IsOdd
{
	ReplaceIf_Predicate_IsOdd(){}
	bool operator()(int value)
	{
		return ((value % 2) == 1);
	}
};

struct ReplaceIf_Predicate
{
	int removeValue_;
	ReplaceIf_Predicate(int removeValue) : removeValue_(removeValue){}
	bool operator()(ReplaceIf_Data& t1)
	{
		return (t1.pos_ == removeValue_);
	}
};

BEGIN_TEST(ReplaceIf)
  vector<int> myvector;
  vector<int>::iterator it;

  // set some values:
  for (int i=1; i<10; i++) myvector.push_back(i);          // 1 2 3 4 5 6 7 8 9
  
  replace_if (myvector.begin(), myvector.end(), ReplaceIf_Predicate_IsOdd(), 0); // 0 2 0 4 0 6 0 8 0

  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;
 
    
  vector<ReplaceIf_Data> o;
  o.push_back(ReplaceIf_Data(0));
  o.push_back(ReplaceIf_Data(1));
  o.push_back(ReplaceIf_Data(1));
  o.push_back(ReplaceIf_Data(1));
  o.push_back(ReplaceIf_Data(2));
  o.push_back(ReplaceIf_Data(3));
  o.push_back(ReplaceIf_Data(4));
  o.push_back(ReplaceIf_Data(5));
	replace_if(o.begin(),o.end(), ReplaceIf_Predicate(1),ReplaceIf_Data(99));

END_TEST()
