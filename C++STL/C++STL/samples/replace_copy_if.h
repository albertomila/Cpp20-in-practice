#include "StdAfx.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct ReplaceCopyIf_Predicate_IsOdd
{
	ReplaceCopyIf_Predicate_IsOdd() {}
	bool operator()(int value)
	{
		return ((value % 2) == 1);
	}
};

BEGIN_TEST(ReplaceCopyIf)
  vector<int> first,second;
  vector<int>::iterator it;

  // set some values:
  for (int i=1; i<10; i++) first.push_back(i);          // 1 2 3 4 5 6 7 8 9

  second.resize(first.size());   // allocate space
  replace_copy_if (first.begin(), first.end(), second.begin(), ReplaceCopyIf_Predicate_IsOdd(), 0);
                                                        // 0 2 0 4 0 6 0 8 0

  cout << "second contains:";
  for (it=second.begin(); it!=second.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()
