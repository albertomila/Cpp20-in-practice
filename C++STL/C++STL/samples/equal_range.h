#pragma once
#include "stdafx.h"
using namespace std;

struct EqualRange_Data
{
	int pos_;
	EqualRange_Data() : pos_(0){}
	EqualRange_Data(int pos) : pos_(pos){}
	bool operator > (const EqualRange_Data& t)
	{
		return pos_ > t.pos_;
	}
};

struct EqualRange_Predicate
{
	EqualRange_Predicate(){}
	bool operator()(const EqualRange_Data& t1,const EqualRange_Data& t2)
	{
		return t1.pos_ > t2.pos_;
	}
};


struct EqualRange_Predicate_int
{
	EqualRange_Predicate_int(){}
	bool operator()(int i, int j)
	{
		return i > j;
	}
};

BEGIN_TEST(EqualRange)
  int myints[] = {10,20,30,30,20,10,10,20};
  vector<int> v(myints,myints+8);                         // 10 20 30 30 20 10 10 20
  pair<vector<int>::iterator,vector<int>::iterator> bounds;

  // using default comparison:
  sort (v.begin(), v.end());                              // 10 10 10 20 20 20 30 30
  bounds=equal_range (v.begin(), v.end(), 20);            //          ^        ^

  // using "mygreater" as comp:
  sort (v.begin(), v.end(), EqualRange_Predicate_int());                   // 30 30 20 20 20 10 10 10
  bounds=equal_range (v.begin(), v.end(), 20, EqualRange_Predicate_int()); //       ^        ^

  cout << "bounds at positions " << int(bounds.first - v.begin());
  cout << " and " << int(bounds.second - v.begin()) << endl;

  
  vector<int> w(myints,myints+8);  
  sort (w.begin(), w.end(),EqualRange_Predicate_int());         
  bounds=equal_range (w.begin(), w.end(), 20, EqualRange_Predicate_int());

  
  vector<EqualRange_Data> o;
  o.push_back(EqualRange_Data(0));
  o.push_back(EqualRange_Data(1));
  o.push_back(EqualRange_Data(1));
  o.push_back(EqualRange_Data(1));
  o.push_back(EqualRange_Data(2));
  o.push_back(EqualRange_Data(3));
  o.push_back(EqualRange_Data(4));
  o.push_back(EqualRange_Data(5));
  sort (o.begin(), o.end(),EqualRange_Predicate());     
  pair<vector<EqualRange_Data>::iterator,vector<EqualRange_Data>::iterator> boundsTest;
  boundsTest=equal_range (o.begin(), o.end(), EqualRange_Data(1), EqualRange_Predicate());

END_TEST()