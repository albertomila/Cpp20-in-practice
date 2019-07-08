#pragma once
#include "stdafx.h"
using namespace std;


struct Partition_Predicate_IsOdd
{
	Partition_Predicate_IsOdd() {}
	bool operator()(int value)
	{
		return ((value % 2) == 1);
	}
};

struct Partition_Data
{
	int pos_;
	Partition_Data() : pos_(0){}
	Partition_Data(int pos) : pos_(pos){}
};

struct Partition_Predicate
{
	Partition_Predicate() {}
	bool operator()(Partition_Data& t1)
	{
		return (t1.pos_ % 3 == 0);
	}
};


BEGIN_TEST(Partition)
  vector<int> myvector;
  vector<int>::iterator it, bound;

  // set some values:
  for (int i=1; i<10; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  bound = partition (myvector.begin(), myvector.end(), Partition_Predicate_IsOdd());

  // print out content:
  cout << "odd members:";
  for (it=myvector.begin(); it!=bound; ++it)
    cout << " " << *it;

  cout << "\neven members:";
  for (it=bound; it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;


  vector<Partition_Data> o;
  o.push_back(Partition_Data(0));
  o.push_back(Partition_Data(1));
  o.push_back(Partition_Data(2));
  o.push_back(Partition_Data(3));
  o.push_back(Partition_Data(4));
  o.push_back(Partition_Data(5));
  o.push_back(Partition_Data(6));
  o.push_back(Partition_Data(7));
  vector<Partition_Data>::iterator itt, boundd;
  
  boundd = partition(o.begin(),o.end(), Partition_Predicate());
  
  // print out content:
  cout << "odd members:";
  for (itt=o.begin(); itt!=boundd; ++itt)
	  cout << " " << (*itt).pos_;

  cout << "\neven members:";
  for (itt=boundd; itt!=o.end(); ++itt)
    cout << " " << (*itt).pos_;

  
  vector<Partition_Data> u,v;
  u.resize(boundd - o.begin());
  v.resize(o.end() - boundd);
  copy(o.begin(), boundd, u.begin());
  copy(boundd,o.end(),v.begin());

END_TEST()
