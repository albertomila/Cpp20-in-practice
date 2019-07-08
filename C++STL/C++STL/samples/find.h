#pragma once
#include "stdafx.h"
using namespace std;

struct Find_Data
{
	int pos_;
	Find_Data() : pos_(0){}
	Find_Data(int pos) : pos_(pos){}
	bool operator == (const Find_Data& t)
	{
		return pos_ == t.pos_;
	}
};

BEGIN_TEST(Find)
  int myints[] = { 10, 20, 30 ,40 };
  int * p;

  // pointer to array element:
  p = find(myints,myints+4,30);
  ++p;
  cout << "The element following 30 is " << *p << endl;

  vector<int> myvector (myints,myints+4);
  vector<int>::iterator it;

  // iterator to vector element:
  it = find (myvector.begin(), myvector.end(), 30);
  ++it;
  cout << "The element following 30 is " << *it << endl;

  
  vector<Find_Data> o;
  o.push_back(Find_Data(0));
  o.push_back(Find_Data(1));
  o.push_back(Find_Data(2));
  o.push_back(Find_Data(3));
  o.push_back(Find_Data(4));
  o.push_back(Find_Data(5));
  vector<Find_Data>::iterator itt = find(o.begin(), o.end(), Find_Data(4));

END_TEST()