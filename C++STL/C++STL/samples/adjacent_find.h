#pragma once
#include "stdafx.h"
using namespace std;

struct AdjacentFind_Predicate
{
	bool operator()(int i, int j)
	{
		return i==j;
	}
};


BEGIN_TEST(AdjacentFind)
  int myints[] = {10,20,30,30,30,10,10,20};
  vector<int> myvector (myints,myints+8);
  vector<int>::iterator it;

  // using default comparison:
  it = adjacent_find (myvector.begin(), myvector.end());
  if (it!=myvector.end())
    cout << "the first consecutive repeated elements are: " << *it << endl;

  //using predicate comparison:
  it = adjacent_find (++it, myvector.end(), AdjacentFind_Predicate());
  if (it!=myvector.end())
    cout << "the second consecutive repeated elements are: " << *it << endl;

END_TEST()