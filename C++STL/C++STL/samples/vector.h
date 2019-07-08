#pragma once
#include "stdafx.h"
using namespace std;

struct Vector_Data
{
	int pos_;
	int* pointer_;
	Vector_Data() : pos_(99)
	{
		pointer_ = new int[10];
	}
	Vector_Data(int pos) : pos_(pos) {}
	~Vector_Data()
	{
		pos_ = 100;
		delete[] pointer_;
	}

	bool operator > (const Vector_Data& t)
	{
		return pos_ > t.pos_;
	}
};

class Vector : public ITest		
{									
public:								
	virtual ~Vector() {}			
	virtual void Run() override
	{
		Example1();
		Example2();
		Example3();
		Example4();
		Example5();
		Example6();
		Example7();
		Example8();
	}

private:
	void Example1();
	void Example2();
	void Example3();
	void Example4();
	void Example5();
	void Example6();
	void Example7();
	void Example8();
};