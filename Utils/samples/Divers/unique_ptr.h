#pragma once
#include "stdafx.h"
#include <memory>
using namespace std;
struct UniquePtr_Data
{
	int pos_;
	UniquePtr_Data() : pos_(0){}
	UniquePtr_Data(int pos) : pos_(pos){}
	~UniquePtr_Data()
	{
		int x = 0;
		x = 0;
	}
};

struct UniquePtr_Data2
{
	int pos_;
	char* chr_;
	UniquePtr_Data2() : pos_(0){}
	UniquePtr_Data2(int pos, char* chr) : pos_(pos), chr_(chr){}
	~UniquePtr_Data2()
	{
	}
};

BEGIN_TEST(UniquePtr)
	 unique_ptr<UniquePtr_Data> t1 =  unique_ptr<UniquePtr_Data>(new UniquePtr_Data(99));
	 t1->pos_ = 10;
	 /*
	 unique_ptr<UniquePtr_Data> t2 = unique_ptr<UniquePtr_Data>(t1.get());
	 t2->pos_ = 20;			//crash when t1 delete
	 */
	 /*
	 UniquePtr_Data* t3 = t1.get();
	 delete t3;				//crash when t1 delete
	 
	 */

	 END_TEST()
