#pragma once
#include "stdafx.h"
using namespace std;

struct RemoveIf_Predicate_IsOdd
{
	RemoveIf_Predicate_IsOdd() {}
	bool operator()(int value)
	{
		return ((value % 2) == 1);
	}
};


struct RemoveIf_Data
{
	int pos_;
	RemoveIf_Data() : pos_(0){}
	RemoveIf_Data(int pos) : pos_(pos){}
};
struct RemoveIf_Predicate
{
	int removeValue_;
	RemoveIf_Predicate(int removeValue) : removeValue_(removeValue){}
	bool operator()(RemoveIf_Data& t1)
	{
		return (t1.pos_ == removeValue_);
	}
};

BEGIN_TEST(RemoveIf)
  int myints[] = {1,2,3,4,5,6,7,8,9};            // 1 2 3 4 5 6 7 8 9

  // bounds of range:
  int* pbegin = myints;                          // ^
  int* pend = myints+sizeof(myints)/sizeof(int); // ^                 ^

  pend = remove_if (pbegin, pend, RemoveIf_Predicate_IsOdd());        // 2 4 6 8 5 6 7 8 9
                                                 // ^       ^
  cout << "range contains:";
  for (int* p=pbegin; p!=pend; ++p)
    cout << " " << *p;

  cout << endl;
 
  
	vector<RemoveIf_Data> o;
	o.push_back(RemoveIf_Data(0));
	o.push_back(RemoveIf_Data(1));
	o.push_back(RemoveIf_Data(1));
	o.push_back(RemoveIf_Data(1));
	o.push_back(RemoveIf_Data(2));
	o.push_back(RemoveIf_Data(3));
	o.push_back(RemoveIf_Data(4));
	o.push_back(RemoveIf_Data(5));
	remove_if(o.begin(),o.end(),RemoveIf_Predicate(1));

END_TEST()