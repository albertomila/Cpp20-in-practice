#pragma once
#include "stdafx.h"
using namespace std;


BEGIN_TEST(ReverseCopy)
  int myints[] ={1,2,3,4,5,6,7,8,9};
  vector<int> myvector;
  vector<int>::iterator it;

  myvector.resize(9);

  reverse_copy (myints, myints+9, myvector.begin());

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()
