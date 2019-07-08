#pragma once
#include "stdafx.h"
using namespace std;

struct Transform_Predicate_Increase
{
	int operator()(int i)
	{
		return ++i;
	}
};

struct Transform_Predicate_Sum
{
	int operator()(int i, int j) 
	{
		return i + j;
	}
};

struct Transform_test
{
	int pos_;
	Transform_test() : pos_(0){}
	Transform_test(int pos) : pos_(pos){}
};


struct Transform_predTest
{
	Transform_predTest() {}
	Transform_test operator()(const Transform_test& t1)
	{
		return Transform_test(t1.pos_ * 100);
	}
	Transform_test operator()(const Transform_test& t1,const Transform_test& t2)
	{
		return Transform_test(t1.pos_ * t2.pos_);
	}
};

BEGIN_TEST(Transform)
	vector<int> first;
	vector<int> second;
	vector<int>::iterator it;

	// set some values:
	for (int i = 1; i < 6; i++) first.push_back(i * 10); //  first: 10 20 30 40 50

	second.resize(first.size());     // allocate space
	transform(first.begin(), first.end(), second.begin(), Transform_Predicate_Increase());
	// second: 11 21 31 41 51

	transform(first.begin(), first.end(), second.begin(), first.begin(), Transform_Predicate_Sum());
	//  first: 21 41 61 81 101

	cout << "first contains:";
	for (it = first.begin(); it != first.end(); ++it)
	cout << " " << *it;

	cout << endl;


	vector<Transform_test> o;
	o.push_back(Transform_test(0));
	o.push_back(Transform_test(1));
	o.push_back(Transform_test(2));
	o.push_back(Transform_test(3));
	o.push_back(Transform_test(4));
	o.push_back(Transform_test(5));

	vector<Transform_test> v(6);
	v.push_back(Transform_test(10));
	v.push_back(Transform_test(11));
	v.push_back(Transform_test(12));
	v.push_back(Transform_test(13));
	v.push_back(Transform_test(14));
	v.push_back(Transform_test(15));

	transform(o.begin(), o.end(), v.begin(), Transform_predTest());


	o.clear();
	o.push_back(Transform_test(0));
	o.push_back(Transform_test(1));
	o.push_back(Transform_test(2));
	o.push_back(Transform_test(3));
	o.push_back(Transform_test(4));
	o.push_back(Transform_test(5));

	v.clear();
	v.push_back(Transform_test(10));
	v.push_back(Transform_test(11));
	v.push_back(Transform_test(12));
	v.push_back(Transform_test(13));
	v.push_back(Transform_test(14));
	v.push_back(Transform_test(15));

	transform(o.begin(), o.end(), v.begin(), v.begin(), Transform_predTest());

END_TEST()