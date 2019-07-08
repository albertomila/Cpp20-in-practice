#pragma once
#include "stdafx.h"
using namespace std;

struct Equal_Data
{
	int pos_;
	Equal_Data() : pos_(0){}
	Equal_Data(int pos) : pos_(pos){}
	bool operator == (const Equal_Data& t)
	{
		return pos_ == t.pos_;
	}
};

struct Equal_Predicate
{
	Equal_Predicate(){}
	bool operator()(Equal_Data& t1, Equal_Data& t2)
	{
		return t1 == t2;
	}
};

struct Equal_Predicate_int
{
	bool operator()(int i, int j)
	{
		return (i == j);
	}
};

BEGIN_TEST(Equal)
  int myints[] = {20,40,60,80,100};          //   myints: 20 40 60 80 100
  vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

  // using default comparison:
  if (equal (myvector.begin(), myvector.end(), myints))
    cout << "The contents of both sequences are equal." << endl;
  else
    cout << "The contents of both sequences differ." << endl;

  myvector[3]=81;                            // myvector: 20 40 60 81 100

  // using predicate comparison:
  if (equal (myvector.begin(), myvector.end(), myints, Equal_Predicate_int()))
    cout << "The contents of both sequences are equal." << endl;
  else
    cout << "The contents of both sequences differ." << endl;
  

  
  
  vector<Equal_Data> origin;
  origin.push_back(Equal_Data(0));
  origin.push_back(Equal_Data(1));
  origin.push_back(Equal_Data(2));
  origin.push_back(Equal_Data(3));
  origin.push_back(Equal_Data(4));
  origin.push_back(Equal_Data(5));

  vector<Equal_Data> destiny;
  destiny.resize(6);
  copy(origin.begin(),origin.end(), destiny.begin());

  bool x = equal (origin.begin(), origin.end(), destiny.begin(), Equal_Predicate());

END_TEST()