#pragma once
#include "stdafx.h"

using namespace std;

struct Unique_CopyPredicate
{
	Unique_CopyPredicate() {}
	bool operator()(int i, int j)
	{
		return (i == j);
	}
};

BEGIN_TEST(UniqueCopy)
  int myints[] = {10,20,20,20,30,30,20,20,10};
  vector<int> myvector (9);                            // 0  0  0  0  0  0  0  0  0
  vector<int>::iterator it;

  // using default comparison:
  it=unique_copy (myints,myints+9,myvector.begin());   // 10 20 30 20 10 0  0  0  0
                                                       //                ^

  sort (myvector.begin(),it);                          // 10 10 20 20 30 0  0  0  0
                                                       //                ^

  // using predicate comparison:
  it=unique_copy (myvector.begin(), it, myvector.begin(), Unique_CopyPredicate());
                                                       // 10 20 30 20 30 0  0  0  0
                                                       //          ^

  myvector.resize( it - myvector.begin() );            // 10 20 30

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()