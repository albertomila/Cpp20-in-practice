#pragma once
#include "stdafx.h"
#include <cctype>
using namespace std;

struct FindFirstOf_Predicate_comp_case_insensitive
{
	bool operator()(char c1, char c2)
	{
		return tolower(c1) == tolower(c2);
	}
};

BEGIN_TEST(FindFirstOf)
  int mychars[] = {'a','b','c','A','B','C'};
  vector<char> myvector (mychars,mychars+6);
  vector<char>::iterator it;

  int match[] = {'A','B','C'};

  // using default comparison:
  it = find_first_of (myvector.begin(), myvector.end(), match, match+3);

  if (it!=myvector.end())
    cout << "first match is: " << *it << endl;

  // using predicate comparison:
  it = find_first_of (myvector.begin(), myvector.end(), match, match+3, FindFirstOf_Predicate_comp_case_insensitive());

  if (it!=myvector.end())
    cout << "first match is: " << *it << endl;

END_TEST()