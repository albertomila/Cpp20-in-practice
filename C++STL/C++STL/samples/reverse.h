#pragma once
#include "stdafx.h"
using namespace std;

struct Reverse_Data
{
	int pos_;
	Reverse_Data() : pos_(0){}
	Reverse_Data(int pos) : pos_(pos){}
};


BEGIN_TEST(Reverse)
  vector<int> myvector;
  vector<int>::iterator it;

  // set some values:
  for (int i=1; i<10; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  reverse(myvector.begin(),myvector.end());       // 9 8 7 6 5 4 3 2 1

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;
  
  vector<Reverse_Data> o;
  o.push_back(Reverse_Data(0));
  o.push_back(Reverse_Data(1));
  o.push_back(Reverse_Data(2));
  o.push_back(Reverse_Data(3));
  o.push_back(Reverse_Data(4));
  o.push_back(Reverse_Data(5));
  reverse(o.begin(),o.end()); 

END_TEST()
