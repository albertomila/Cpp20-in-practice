#pragma once
#include "stdafx.h"
using namespace std;

struct Remove_Data
{
	int pos_;
	Remove_Data() : pos_(0){}
	Remove_Data(int pos) : pos_(pos){}
	bool operator == (const Remove_Data& t)
	{
		return pos_ == t.pos_;
	}
	bool operator == (const Remove_Data* t)
	{
		return this == t;
	}
};

BEGIN_TEST(Remove)
  int myints[] = {10,20,30,30,20,10,10,20};      // 10 20 30 30 20 10 10 20

  // bounds of range:
  int* pbegin = myints;                          // ^
  int* pend = myints+sizeof(myints)/sizeof(int); // ^                       ^
  
  cout << "range contains:";
  for (int* p=pbegin; p!=pend; ++p)
    cout << " " << *p;
  cout << endl;

  pend = remove (pbegin, pend, 20);              // 10 30 30 10 10 10 10 20
                                                 // ^              ^
  cout << "range contains:";
  for (int* p=pbegin; p!=pend; ++p)
    cout << " " << *p;

  cout << endl;
 
	vector<Remove_Data> o;
	o.push_back(Remove_Data(0));
	o.push_back(Remove_Data(1));
	o.push_back(Remove_Data(1));
	o.push_back(Remove_Data(1));
	o.push_back(Remove_Data(2));
	o.push_back(Remove_Data(3));
	o.push_back(Remove_Data(4));
	o.push_back(Remove_Data(5));
	vector<Remove_Data>::iterator itt = remove(o.begin(),o.end(),Remove_Data(1));

END_TEST()