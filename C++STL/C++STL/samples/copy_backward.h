#pragma once
#include "stdafx.h"
using namespace std;


BEGIN_TEST(CopyBackward)
  vector<int> myvector;
  vector<int> myvector2;
  vector<int>::iterator it;

  // set some values:
  for (int i=1; i<=5; i++)
    myvector.push_back(i*10);          // myvector: 10 20 30 40 50

  myvector2.resize(myvector.size() + 3);  // myvector2: 0 0 0 0 0 0 0 0 

  copy_backward ( myvector.begin(), myvector.begin()+5, myvector2.end() );
   // myvector2: 0 0 0 10 20 30 40 50

  cout << "myvector contains:";
  for (it=myvector2.begin(); it!=myvector2.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()