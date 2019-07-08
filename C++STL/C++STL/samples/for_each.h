#pragma once
#include "stdafx.h"
using namespace std;

struct ForEach_Predicate_Print 
{
  void operator() (int i) 
  {
	  cout << " " << i;
  }
};

struct ForEach_Data
{
	int pos_;
	ForEach_Data() : pos_(0){}
	ForEach_Data(int pos) : pos_(pos){}
	bool operator > (const ForEach_Data& t)
	{
		return pos_ > t.pos_;
	}
};

struct ForEach_Predicate
{
	ForEach_Predicate() {}
	void operator()(ForEach_Data& t1)
	{
		t1.pos_  = 1;
	}
};

BEGIN_TEST(ForEach)
  vector<int> myvector;
  myvector.push_back(10);
  myvector.push_back(20);
  myvector.push_back(30);

  cout << "\nmyvector contains:";
  for_each (myvector.begin(), myvector.end(), ForEach_Predicate_Print());

  cout << endl;

  vector<ForEach_Data> o;
  o.push_back(ForEach_Data(0));
  o.push_back(ForEach_Data(1));
  o.push_back(ForEach_Data(1));
  o.push_back(ForEach_Data(1));
  o.push_back(ForEach_Data(2));
  o.push_back(ForEach_Data(3));
  o.push_back(ForEach_Data(4));
  o.push_back(ForEach_Data(5));
  ForEach_Predicate c = for_each (o.begin(), o.end(), ForEach_Predicate());

END_TEST()