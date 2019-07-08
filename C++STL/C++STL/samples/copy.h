#pragma once
#include "stdafx.h"
using namespace std;

struct Copy_Data
{
	int pos_;
	Copy_Data() : pos_(0){}
	Copy_Data(int pos) : pos_(pos){}
};


BEGIN_TEST(Copy)
  int myints[]={10,20,30,40,50,60,70};
  int myints2[7];
  vector<int> myvector;
  vector<int>::iterator it;

  
  vector<Copy_Data> origin;
  vector<Copy_Data> destiny;
  origin.push_back(Copy_Data(0));
  origin.push_back(Copy_Data(1));
  origin.push_back(Copy_Data(2));
  origin.push_back(Copy_Data(3));
  origin.push_back(Copy_Data(4));
  origin.push_back(Copy_Data(5));
  destiny.resize(6);

  myvector.resize(7);   // allocate space for 7 elements

  copy(myints, myints+7, myvector.begin());
  copy(myvector.begin(), myvector.end(), myints2);
  copy(origin.begin(), origin.end(), destiny.begin());
  
  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;

END_TEST()