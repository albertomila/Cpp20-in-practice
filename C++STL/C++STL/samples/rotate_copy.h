#pragma once
#include "stdafx.h"
using namespace std;

struct RotateCopy_Data
{
	int pos_;
	RotateCopy_Data() : pos_(0){}
	RotateCopy_Data(int pos) : pos_(pos){}
};


BEGIN_TEST(RotateCopy)
  int myints[] = {10,20,30,40,50,60,70};

  vector<int> myvector;
  vector<int>::iterator it;

  myvector.resize(7);

  rotate_copy(myints,myints+3,myints+7,myvector.begin());

  // print out content:
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;
  
  vector<RotateCopy_Data> o,v;
  o.push_back(RotateCopy_Data(0));
  o.push_back(RotateCopy_Data(1));
  o.push_back(RotateCopy_Data(2));
  o.push_back(RotateCopy_Data(3));
  o.push_back(RotateCopy_Data(4));
  o.push_back(RotateCopy_Data(5));
  v.resize(o.size());
  rotate_copy(o.begin(),o.begin()+3,o.end(),v.begin());


END_TEST()
