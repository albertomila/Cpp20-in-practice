#pragma once
#include "stdafx.h"
using namespace std;


struct Fill_Data
{
	int pos_;
	Fill_Data() : pos_(0){}
	Fill_Data(int pos) : pos_(pos){}
};

BEGIN_TEST(Fill)
  vector<int> myvector (8);                       // myvector: 0 0 0 0 0 0 0 0

  fill (myvector.begin(),		myvector.begin() + 4,	5);   // myvector: 5 5 5 5 0 0 0 0
  fill (myvector.begin() + 3,	myvector.end() - 2,		8);   // myvector: 5 5 5 8 8 8 0 0

  cout << "myvector contains:";
  for (vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;
 
  vector<Fill_Data> o;
  o.push_back(Fill_Data(0));
  o.push_back(Fill_Data(1));
  o.push_back(Fill_Data(2));
  o.push_back(Fill_Data(3));
  o.push_back(Fill_Data(4));
  o.push_back(Fill_Data(5));
  fill(o.begin(), o.end(), Fill_Data(0));

END_TEST()