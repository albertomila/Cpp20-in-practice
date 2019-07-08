#pragma once
#include "stdafx.h"
using namespace std;

struct SearchN_Data
{
	int pos_;
	SearchN_Data() : pos_(0){}
	SearchN_Data(int pos) : pos_(pos){}
};


struct SearchN_Predicate
{
	SearchN_Predicate() {}
	bool operator()(const SearchN_Data& t1,const SearchN_Data& t2)
	{
		return t1.pos_ == t2.pos_;
	}
};

BEGIN_TEST(SearchN)
  int myints[]={10,20,30,30,20,10,10,20};
  vector<int> myvector (myints,myints+8);

  vector<int>::iterator it;

  // using default comparison:
  it = search_n (myvector.begin(), myvector.end(), 2, 30);

  if (it!=myvector.end())
    cout << "two 30s found at position " << int(it-myvector.begin()) << endl;
  else
    cout << "match not found" << endl;

  // using predicate comparison:
  it = search_n (myvector.begin(), myvector.end(), 2, 10, SearchN_Predicate());

  if (it!=myvector.end())
    cout << "two 10s found at position " << int(it-myvector.begin()) << endl;
  else
    cout << "match not found" << endl;
  
  
  vector<SearchN_Data> o;
  o.push_back(SearchN_Data(0));
  o.push_back(SearchN_Data(99));
  o.push_back(SearchN_Data(99));
  o.push_back(SearchN_Data(99));
  o.push_back(SearchN_Data(4));
  o.push_back(SearchN_Data(5));
  
  vector<SearchN_Data>::iterator itt;
  itt =search_n(o.begin(),o.end(),2, SearchN_Data(99), SearchN_Predicate());
  
  if (itt!=o.end())
    cout << "two 99s found at position " << int(itt-o.begin()) << endl;
  else
    cout << "match not found" << endl;


END_TEST()
