#pragma once
#include "stdafx.h"
using namespace std;

struct StablePartition_Predicate_IsOdd
{
	bool operator()(int value)
	{
		return ((value % 2) == 1);
	}
};

BEGIN_TEST(StablePartition)
  vector<int> myvector;
  vector<int>::iterator it, bound;

  // set some values:
  for (int i=1; i<10; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  bound = stable_partition (myvector.begin(), myvector.end(), StablePartition_Predicate_IsOdd());

  // print out content:
  cout << "odd members:";
  for (it=myvector.begin(); it!=bound; ++it)
    cout << " " << *it;

  cout << "\neven members:";
  for (it=bound; it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()