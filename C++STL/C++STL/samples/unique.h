#pragma once
#include "StdAfx.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Unique_test
{
	int pos_;
	Unique_test() : pos_(0){}
	Unique_test(int pos) : pos_(pos){}
};
struct Unique_predTest
{
	Unique_predTest() {}
	bool operator()(const Unique_test& t1,const Unique_test& t2)
	{
		return t1.pos_ == t2.pos_;
	}
};

BEGIN_TEST(Unique)
  int myints[] = {10,20,20,20,30,30,20,20,10};    // 10 20 20 20 30 30 20 20 10
  vector<int> myvector (myints,myints+9);
  vector<int>::iterator it;

  // using default comparison:
  it = unique (myvector.begin(), myvector.end()); // 10 20 30 20 10 30 20 20 10
                                                  //                ^

  myvector.resize( it - myvector.begin() );       // 10 20 30 20 10

  // using predicate comparison:
  unique (myvector.begin(), myvector.end(), Unique_predTest());   // (no changes)

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

  vector<Unique_test> o;
  o.push_back(Unique_test(0));
  o.push_back(Unique_test(1));
  o.push_back(Unique_test(1));
  o.push_back(Unique_test(3));
  o.push_back(Unique_test(3));
  o.push_back(Unique_test(5));
  unique (o.begin(), o.end(), Unique_predTest());

END_TEST()