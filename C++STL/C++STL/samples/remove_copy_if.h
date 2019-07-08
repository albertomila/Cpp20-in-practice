#pragma once
#include "stdafx.h"
using namespace std;

struct RemoveCopyIf_Predicate_IsOdd
{
	RemoveCopyIf_Predicate_IsOdd() {}
	bool operator()(int value)
	{
		return ((value % 2) == 1);
	}
};

struct RemoveCopyIf_Data
{
	int pos_;
	RemoveCopyIf_Data() : pos_(0){}
	RemoveCopyIf_Data(int pos) : pos_(pos){}
};
struct RemoveCopyIf_Predicate
{
	int removeValue_;
	RemoveCopyIf_Predicate(int removeValue) : removeValue_(removeValue){}
	bool operator()(RemoveCopyIf_Data& t1)
	{
		return (t1.pos_ == removeValue_);
	}
};

BEGIN_TEST(RemoveCopyIf)
  int myints[] = {1,2,3,4,5,6,7,8,9};          
  vector<int> myvector (9);
  vector<int>::iterator it;

  remove_copy_if (myints,myints+9,myvector.begin(), RemoveCopyIf_Predicate_IsOdd());

  cout << "myvector contains:";
  for (it=myvector.begin(); it!=myvector.end(); ++it)
    cout << " " << *it;

  cout << endl;
 

  
	vector<RemoveCopyIf_Data> o;
	vector<RemoveCopyIf_Data> v;
	v.resize(10);
	o.push_back(RemoveCopyIf_Data(0));
	o.push_back(RemoveCopyIf_Data(1));
	o.push_back(RemoveCopyIf_Data(1));
	o.push_back(RemoveCopyIf_Data(1));
	o.push_back(RemoveCopyIf_Data(2));
	o.push_back(RemoveCopyIf_Data(3));
	o.push_back(RemoveCopyIf_Data(4));
	o.push_back(RemoveCopyIf_Data(5));
	remove_copy_if(o.begin(),o.end(),v.begin(),RemoveCopyIf_Predicate(1));

END_TEST()