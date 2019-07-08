#pragma once
#include "stdafx.h"
using namespace std;

struct NextPermutation_Data
{
	int pos_;
	NextPermutation_Data() : pos_(0){}
	NextPermutation_Data(int pos) : pos_(pos){}
};

struct NextPermutation_Predicate
{
	NextPermutation_Predicate() {}
	bool operator()(const NextPermutation_Data& t0,const NextPermutation_Data& t1)
	{
		return t0.pos_ < t1.pos_;
	}
};

struct NextPermutation_Print
{
	NextPermutation_Print() {}
	void operator()(const NextPermutation_Data& t0)
	{
		cout << t0.pos_ << ' ';
	}
};

struct NextPermutation_GenTest
{
	int max_;
	int count_;
	NextPermutation_GenTest(int max) : max_(max), count_(-1) {}
	NextPermutation_Data operator()()
	{
		++count_;
		return NextPermutation_Data(count_);
	}
};

BEGIN_TEST(NextPermutation)
  int myints[] = {1,2,3};

  cout << "The 3! possible permutations with 3 elements:\n";

  sort (myints,myints+3);

  do 
  {
    cout << myints[0] << " " << myints[1] << " " << myints[2] << endl;
  }
  while ( next_permutation(myints,myints+3) );

  vector<NextPermutation_Data> o;
  o.resize(3);
  generate(o.begin(), o.end(), NextPermutation_GenTest(100));

  do 
  {
	  for_each(o.begin(),o.end(),NextPermutation_Print());
	  cout << endl;
  }
  while ( next_permutation(o.begin(),o.end(),NextPermutation_Predicate()) );

END_TEST()
