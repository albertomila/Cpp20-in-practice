#pragma once
#include "stdafx.h"
using namespace std;

struct RemoveCopy_Data
{
	int pos_;
	RemoveCopy_Data() : pos_(0){}
	RemoveCopy_Data(int pos) : pos_(pos){}
	bool operator == (const RemoveCopy_Data& t)
	{
		return pos_ == t.pos_;
	}
	bool operator == (const RemoveCopy_Data* t)
	{
		return this == t;
	}
};


BEGIN_TEST(RemoveCopy)
  int myints[] = {10,20,30,30,20,10,10,20};          // 10 20 30 30 20 10 10 20
  vector<int> myvector (8);
  vector<int>::iterator it;

  remove_copy (myints,myints+8,myvector.begin(),20); // 10 30 30 10 10 0 0 0

  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;
 
  vector<RemoveCopy_Data> o;
  vector<RemoveCopy_Data> v;
  v.resize(10);
	o.push_back(RemoveCopy_Data(0));
	o.push_back(RemoveCopy_Data(1));
	o.push_back(RemoveCopy_Data(1));
	o.push_back(RemoveCopy_Data(1));
	o.push_back(RemoveCopy_Data(2));
	o.push_back(RemoveCopy_Data(3));
	o.push_back(RemoveCopy_Data(4));
	o.push_back(RemoveCopy_Data(5));
	remove_copy(o.begin(),o.end(),v.begin(),RemoveCopy_Data(1));

END_TEST()