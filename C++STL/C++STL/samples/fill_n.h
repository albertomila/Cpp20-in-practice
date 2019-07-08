#pragma once
#include "stdafx.h"
using namespace std;

struct FillN_Data
{
	int pos_;
	FillN_Data() : pos_(0){}
	FillN_Data(int pos) : pos_(pos){}
};


BEGIN_TEST(FillN)
  vector<int> myvector (8,10);        // myvector: 10 10 10 10 10 10 10 10

  fill_n (myvector.begin(),4,20);     // myvector: 20 20 20 20 10 10 10 10
  fill_n (myvector.begin()+3,3,33);   // myvector: 20 20 20 33 33 33 10 10

  cout << "myvector contains:";
  for (vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;
 
  vector<FillN_Data> o;
  o.push_back(FillN_Data(99));
  o.push_back(FillN_Data(98));
  o.push_back(FillN_Data(97));
  o.push_back(FillN_Data(96));
  o.push_back(FillN_Data(95));
  o.push_back(FillN_Data(94));
  fill_n(o.begin() + 1, 3, FillN_Data(7));

END_TEST()