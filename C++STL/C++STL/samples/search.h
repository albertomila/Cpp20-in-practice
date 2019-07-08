#pragma once
#include "stdafx.h"
using namespace std;

struct Search_Data
{
	int pos_;
	Search_Data() : pos_(0){}
	Search_Data(int pos) : pos_(pos){}
};


struct Search_Predicate
{
	Search_Predicate() {}
	bool operator()(const Search_Data& t1,const Search_Data& t2)
	{
		return t1.pos_ == t2.pos_;
	}
};

BEGIN_TEST(Search)
  vector<int> myvector;
  vector<int>::iterator it;

  // set some values:        myvector: 10 20 30 40 50 60 70 80 90
  for (int i=1; i<10; i++) myvector.push_back(i*10);


  // using default comparison:
  int match1[] = {40,50,60,70};
  it = search (myvector.begin(), myvector.end(), match1, match1+4);

  if (it!=myvector.end())
    cout << "match1 found at position " << int(it-myvector.begin()) << endl;
  else
    cout << "match1 not found" << endl;

  // using predicate comparison:
  int match2[] = {20,30,50};
  it = search (myvector.begin(), myvector.end(), match2, match2+3, Search_Predicate());

  if (it!=myvector.end())
    cout << "match2 found at position " << int(it-myvector.begin()) << endl;
  else
    cout << "match2 not found" << endl;
  

  vector<Search_Data> o;
  o.push_back(Search_Data(0));
  o.push_back(Search_Data(1));
  o.push_back(Search_Data(2));
  o.push_back(Search_Data(3));
  o.push_back(Search_Data(4));
  o.push_back(Search_Data(5));

  vector<Search_Data> v;
  v.push_back(Search_Data(2));
  v.push_back(Search_Data(3));
  v.push_back(Search_Data(4));
  
  vector<Search_Data>::iterator itt;
  itt =search(o.begin(),o.end(),v.begin(), v.end(), Search_Predicate());


END_TEST()
