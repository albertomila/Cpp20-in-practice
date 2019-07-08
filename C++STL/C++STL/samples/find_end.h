#pragma once
#include "stdafx.h"
using namespace std;

struct FindEnd_Predicate_Equal
{
	bool operator()(int i, int j)
	{
		return (i == j);
	}
};

BEGIN_TEST(FindEnd)
  int myints[] = {1,2,3,4,5,1,2,3,4,5};
  vector<int> myvector (myints,myints+10);
  vector<int>::iterator it;

  int match1[] = {1,2,3};

  // using default comparison:
  it = find_end (myvector.begin(), myvector.end(), match1, match1+3);

  if (it!=myvector.end())
    cout << "match1 last found at position " << int(it-myvector.begin()) << endl;

  int match2[] = {4,5,1};

  // using predicate comparison:
  it = find_end (myvector.begin(), myvector.end(), match2, match2+3, FindEnd_Predicate_Equal());

  if (it!=myvector.end())
    cout << "match2 last found at position " << int(it-myvector.begin()) << endl;

END_TEST()