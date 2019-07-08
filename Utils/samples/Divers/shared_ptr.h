#pragma once
#include "stdafx.h"
#include <memory>
using namespace std;

struct SharedPtr_Data
{
	int pos_;
	SharedPtr_Data() : pos_(0){}
	SharedPtr_Data(int pos) : pos_(pos){}
	~SharedPtr_Data()
	{
		int x = 0;
		x = 0;
	}
};

struct SharedPtr_Data2
{
	int pos_;
	char* chr_;
	SharedPtr_Data2() : pos_(0){}
	SharedPtr_Data2(int pos, char* chr) : pos_(pos), chr_(chr){}
	~SharedPtr_Data2()
	{
	}
};

BEGIN_TEST(SharedPtr)
	shared_ptr<SharedPtr_Data> t1 = shared_ptr<SharedPtr_Data>(new SharedPtr_Data(99));
	t1.get()->pos_ = 10;
	
	shared_ptr<SharedPtr_Data> t2 = t1;
	t2->pos_ = 20;
	
	shared_ptr<SharedPtr_Data> t3 = t1;
	shared_ptr<SharedPtr_Data> t4 = t1;
	shared_ptr<SharedPtr_Data> t5 = t1;
	shared_ptr<SharedPtr_Data> t6 = t1;

	t6.reset();
	t5.reset();
	t4.reset();
	t3.reset();
	t2.reset();
	t1.reset();


	SharedPtr_Data2* a1 = new SharedPtr_Data2(99,"hola");
	char chr[10] = "hola";
	shared_ptr<SharedPtr_Data2> t10 = make_shared<SharedPtr_Data2>(99, chr);

	END_TEST()