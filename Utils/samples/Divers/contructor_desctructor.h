#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class D
{
public:
	D()
	{
		cout << "7" << endl;
	}
	~D()
	{
		cout << "8" << endl;
	}
};
class C : virtual D
{
public:
	C()
	{
		cout << "5" << endl;
	}
	~C()
	{
		cout << "6" << endl;
	}
};

class A : public virtual D
{
public:
	A()
	{
		cout << "1" << endl;
	}
	~A()
	{
		cout << "2" << endl;
	}
};

class B : public A, public C
{
public:
	B()
	{
		cout << "3" << endl;
	}
	B(const B& b)
	{
	}
	~B()
	{
		cout << "4" << endl;
	}
};
void Prin(B var)
{
}

template<class T>
void foo()
{
	cout << "1" << endl;
}

template<>
void foo<int>()
{
	cout << "2" << endl;
}

template<>
void foo<float>()
{
	cout << "3" << endl;
}

BEGIN_TEST(ConstructorFlow)
	//foo<float>();
	B b;
	//7153, 4628
	//cout << "in" << endl;
	//Prin(b);
	//cout << "out" << endl;

END_TEST()