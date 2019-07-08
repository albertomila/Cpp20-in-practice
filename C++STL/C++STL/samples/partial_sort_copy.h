#pragma once
#include "stdafx.h"
using namespace std;

struct PartialSortCopy_Predicate
{
	PartialSortCopy_Predicate() {}
	bool operator()(int value1, int value2)
	{
		return value1 < value2;
	}
};

BEGIN_TEST(PartialSortCopy)
  int myints[] = {9,8,7,6,5,4,3,2,1};
  vector<int> myvector (5);
  vector<int>::iterator it;

  // using default comparison (operator <):
  partial_sort_copy (myints, myints+9, myvector.begin(), myvector.end());

  // using function as comp
  partial_sort_copy (myints, myints+9, myvector.begin(), myvector.end(), PartialSortCopy_Predicate());

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()
