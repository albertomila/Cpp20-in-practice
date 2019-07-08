#pragma once
#include "stdafx.h"
using namespace std;

struct PartialSort_Predicate
{
	PartialSort_Predicate() {}
	bool operator()(int value1, int value2)
	{
		return value1 < value2;
	}
};


BEGIN_TEST(PartialSort)
  int myints[] = {9,8,7,6,5,4,3,2,1};
  vector<int> myvector (myints, myints+9);
  vector<int>::iterator it;
  //sort(myvector.begin(), myvector.begin()+5);
  // using default comparison (operator <):
  partial_sort (myvector.begin(), myvector.begin()+5, myvector.end());

  // using function as comp
  partial_sort (myvector.begin(), myvector.begin()+5, myvector.end(), PartialSort_Predicate());

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()
