#pragma once
#include "stdafx.h"
using namespace std;

struct NthElement_Predicate
{
	NthElement_Predicate() {}
	bool operator()(int value1, int value2)
	{
		return value1 < value2;
	}
};

BEGIN_TEST(NthElement)
  vector<int> myvector;
  vector<int>::iterator it;

  // set some values:
  myvector.push_back(2);
  myvector.push_back(1);
  myvector.push_back(1);
  myvector.push_back(1);
  myvector.push_back(1);
  myvector.push_back(1);
  myvector.push_back(0);
  myvector.push_back(1);

  random_shuffle (myvector.begin(), myvector.end());

  // using default comparison (operator <):
  nth_element (myvector.begin(), myvector.begin()+5, myvector.end());

  // using function as comp
  nth_element (myvector.begin(), myvector.begin()+5, myvector.end(), NthElement_Predicate());

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()
