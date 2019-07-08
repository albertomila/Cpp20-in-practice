#pragma once
#include "stdafx.h"
using namespace std;

struct Rotate_Data
{
	int pos_;
	Rotate_Data() : pos_(0){}
	Rotate_Data(int pos) : pos_(pos){}
};

BEGIN_TEST(Rotate)
  vector<int> myvector;
  vector<int>::iterator it;

  // set some values:
  for (int i=1; i<10; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  rotate(myvector.begin(),myvector.begin()+3,myvector.end());
                                                  // 4 5 6 7 8 9 1 2 3

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;


  
  vector<Rotate_Data> o;
  o.push_back(Rotate_Data(0));
  o.push_back(Rotate_Data(1));
  o.push_back(Rotate_Data(2));
  o.push_back(Rotate_Data(3));
  o.push_back(Rotate_Data(4));
  o.push_back(Rotate_Data(5));
   rotate(o.begin(),o.begin()+3,o.end());

END_TEST()
