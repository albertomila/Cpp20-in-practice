#pragma once
#include "stdafx.h"
using namespace std;

struct Merge_Data
{
	int pos_;
	Merge_Data() : pos_(0){}
	Merge_Data(int pos) : pos_(pos){}
};

struct Merge_Predicate
{
	Merge_Predicate() {}
	bool operator()(const Merge_Data& t1,const Merge_Data& t2)
	{
		return t1.pos_ < t2.pos_;
	}
};

BEGIN_TEST(Merge)
  int first[] = {5,10,15,20,25};
  int second[] = {50,40,30,20,10};
  vector<int> v(10);
  vector<int>::iterator it;

  sort (first,first+5);
  sort (second,second+5);
  merge (first,first+5,second,second+5,v.begin());
  
  cout << "The resulting vector contains:";
  for (it=v.begin(); it!=v.end(); ++it)
    cout << " " << *it;

  cout << endl;
  

  
  vector<Merge_Data> o;
  o.push_back(Merge_Data(1));
  o.push_back(Merge_Data(2));
  o.push_back(Merge_Data(3));
  o.push_back(Merge_Data(4));
  o.push_back(Merge_Data(5));

  vector<Merge_Data> u;
  u.push_back(Merge_Data(10));
  u.push_back(Merge_Data(20));
  u.push_back(Merge_Data(30));
  u.push_back(Merge_Data(40));
  u.push_back(Merge_Data(50));
  
  vector<Merge_Data> w;
  w.resize(10);

  merge(o.begin(),o.end(),u.begin(),u.end(),w.begin(),Merge_Predicate());

END_TEST()
