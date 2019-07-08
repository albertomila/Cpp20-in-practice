#pragma once
#include "stdafx.h"
using namespace std;

struct Sort_Data
{
	int pos_;
	Sort_Data() : pos_(0){}
	Sort_Data(int pos) : pos_(pos){}
};

struct Sort_Predicate_int
{
	Sort_Predicate_int() {}
	bool operator()(int t1, int t2)
	{
		return t1 < t2;
	}
};


struct Sort_Predicate
{
	Sort_Predicate() {}
	bool operator()(const Sort_Data& t1,const Sort_Data& t2)
	{
		return t1.pos_ < t2.pos_;
	}
};

BEGIN_TEST(Sort)
  int myints[] = {32,71,12,45,26,80,53,33};
  vector<int> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33
  vector<int>::iterator it;

  // using default comparison (operator <):
  sort (myvector.begin(), myvector.begin()+4);           //(12 32 45 71)26 80 53 33

  // using function as comp
  sort (myvector.begin()+4, myvector.end(), Sort_Predicate()); // 12 32 45 71(26 33 53 80)

  // using object as comp
  sort (myvector.begin(), myvector.end(), Sort_Predicate_int());     //(12 26 32 33 45 53 71 80)

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;


   vector<Sort_Data> o;
  o.push_back(Sort_Data(99));
  o.push_back(Sort_Data(45));
  o.push_back(Sort_Data(34));
  o.push_back(Sort_Data(2));
  o.push_back(Sort_Data(1));
  o.push_back(Sort_Data(76));
  sort (o.begin(), o.end(), Sort_Predicate());
END_TEST()