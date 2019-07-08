#pragma once
#include "stdafx.h"
using namespace std;

struct Replace_Data
{
	int pos_;
	Replace_Data() : pos_(0){}
	Replace_Data(int pos) : pos_(pos){}
	bool operator == (const Replace_Data& t)
	{
		return pos_ == t.pos_;
	}
};

BEGIN_TEST(Replace)
  int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
  vector<int> myvector (myints, myints+8);            // 10 20 30 30 20 10 10 20

  replace (myvector.begin(), myvector.end(), 20, 99); // 10 99 30 30 99 10 10 99

  cout << "myvector contains:";
  for (vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;
 
  	vector<Replace_Data> o;
	o.push_back(Replace_Data(0));
	o.push_back(Replace_Data(1));
	o.push_back(Replace_Data(1));
	o.push_back(Replace_Data(1));
	o.push_back(Replace_Data(2));
	o.push_back(Replace_Data(3));
	o.push_back(Replace_Data(4));
	o.push_back(Replace_Data(5));
	replace(o.begin(),o.end(),Replace_Data(1),Replace_Data(99));

END_TEST()