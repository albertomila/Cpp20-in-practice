#pragma once
#include "stdafx.h"
#include <iostream>
#include <memory>
using namespace std;

struct AutoPtr_Data
{
	int pos_;
	AutoPtr_Data() : pos_(0){}
	AutoPtr_Data(int pos) : pos_(pos){}
	~AutoPtr_Data()
	{
		int x = 0;
		x = 0;
	}
};

BEGIN_TEST(AutoPtr)
	/*
	auto_ptr<int> p1 (new int);
	*p1.get()=10;

	auto_ptr<int> p2 (p1);

	cout << "p2 points to " << *p2 << "\n";
	// (p1 is now null-pointer auto_ptr)
	*/

	auto_ptr<AutoPtr_Data> t1 = auto_ptr<AutoPtr_Data>(new AutoPtr_Data(99));
	t1.get()->pos_ = 3;
	
	auto_ptr<AutoPtr_Data> t2;
	t2 = t1;
	t2.get()->pos_ = 100;
	
	auto_ptr<AutoPtr_Data> t3 = auto_ptr<AutoPtr_Data>(t2);
	t3.get()->pos_	= 10;
	(*t3).pos_		= 20;
	t3->pos_			= 30;
	
	AutoPtr_Data* t4 = t3.get();
	t4->pos_ = 40;

	AutoPtr_Data* t5 = t3.release();
	t5->pos_ = 50;
	
	t3.reset(t5);
	t3.get()->pos_ = 60;

	END_TEST()