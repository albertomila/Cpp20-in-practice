#pragma once
#include "stdafx.h"
using namespace std;

struct FindIf_Predicate_IsOdd
{
	FindIf_Predicate_IsOdd() {}
	bool operator()(int value)
	{
		return ((value % 2) == 1);
	}
};

struct FindIf_Data
{
	int pos_;
	FindIf_Data() : pos_(0){}
	FindIf_Data(int pos) : pos_(pos){}
	bool operator > (const FindIf_Data& t)
	{
		return pos_ > t.pos_;
	}
};

struct FindIf_Predicate_Equal
{
	int pos_;
	FindIf_Predicate_Equal(int pos) : pos_(pos){}
	bool operator()(const FindIf_Data& t1)
	{
		return t1.pos_  == pos_;
	}
};

BEGIN_TEST(FindIf)
  vector<int> myvector;
  vector<int>::iterator it;

  myvector.push_back(10);
  myvector.push_back(25);
  myvector.push_back(40);
  myvector.push_back(55);

  it = find_if (myvector.begin(), myvector.end(), FindIf_Predicate_IsOdd());
  cout << "The first odd value is " << *it << endl;

  vector<FindIf_Data> o;
  o.push_back(FindIf_Data(0));
  o.push_back(FindIf_Data(1));
  o.push_back(FindIf_Data(1));
  o.push_back(FindIf_Data(1));
  o.push_back(FindIf_Data(2));
  o.push_back(FindIf_Data(3));
  o.push_back(FindIf_Data(4));
  o.push_back(FindIf_Data(5));
  vector<FindIf_Data>::iterator itt = find_if (o.begin(), o.end(), FindIf_Predicate_Equal(6));

END_TEST()