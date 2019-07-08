#pragma once
#include "stdafx.h"
using namespace std;


BEGIN_TEST(SwapRanges)
  vector<int> first (5,10);        //  first: 10 10 10 10 10
  vector<int> second (5,33);       // second: 33 33 33 33 33
  vector<int>::iterator it;

  swap_ranges(first.begin()+1, first.end()-1, second.begin());

  // print out results of swap:
  cout << " first contains:";
  for (it=first.begin(); it!=first.end(); ++it)
    cout << " " << *it;

  cout << "\nsecond contains:";
  for (it=second.begin(); it!=second.end(); ++it)
    cout << " " << *it;

  cout << endl;
END_TEST()