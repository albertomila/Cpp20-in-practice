#pragma once
#include "stdafx.h"
using namespace std;

struct Mismatch_Data
{
	int pos_;
	Mismatch_Data() : pos_(0){}
	Mismatch_Data(int pos) : pos_(pos){}
};

struct Mismatch_Predicate_int
{
	Mismatch_Predicate_int() {}
	bool operator()(int i, int j)
	{
		return (i == j);
	}
};

struct Mismatch_Predicate
{
	Mismatch_Predicate() {}
	bool operator()(const Mismatch_Data& t1,const Mismatch_Data& t2)
	{
		return t1.pos_  == t2.pos_;
	}
};

BEGIN_TEST(Mismatch)
  vector<int> myvector;
  for (int i=1; i<6; i++) myvector.push_back (i*10); // myvector: 10 20 30 40 50

  int myints[] = {10,20,80,320,1024};                //   myints: 10 20 80 320 1024

  pair<vector<int>::iterator,int*> mypair;

  // using default comparison:
  mypair = mismatch (myvector.begin(), myvector.end(), myints);
  cout << "First mismatching elements: " << *mypair.first;
  cout << " and " << *mypair.second << endl;;

  mypair.first++; mypair.second++;

  // using predicate comparison:
  mypair = mismatch (myvector.begin(), myvector.end(), myints, Mismatch_Predicate_int());
  cout << "Second mismatching elements: " << *mypair.first;
  cout << " and " << *mypair.second << endl;;
  
  
  vector<Mismatch_Data> o;
  o.push_back(Mismatch_Data(1));
  o.push_back(Mismatch_Data(2));
  o.push_back(Mismatch_Data(3));
  o.push_back(Mismatch_Data(4));
  o.push_back(Mismatch_Data(5));

  vector<Mismatch_Data> u;
  u.push_back(Mismatch_Data(1));
  u.push_back(Mismatch_Data(2));
  u.push_back(Mismatch_Data(3));
  u.push_back(Mismatch_Data(40));
  u.push_back(Mismatch_Data(50));
  pair<vector<Mismatch_Data>::iterator,vector<Mismatch_Data>::iterator> testpair;
  testpair = mismatch(o.begin(),o.end(),u.begin(),Mismatch_Predicate());

END_TEST()
