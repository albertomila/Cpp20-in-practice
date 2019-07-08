#pragma once
#include "stdafx.h"
using namespace std;


BEGIN_TEST(ReplaceCopy)
  int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };

  vector<int> myvector (8);
  replace_copy (myints, myints+8, myvector.begin(), 20, 99);

  cout << "myvector contains:";
  for (vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()
