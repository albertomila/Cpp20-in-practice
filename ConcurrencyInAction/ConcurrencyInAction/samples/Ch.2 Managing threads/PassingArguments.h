#include "stdafx.h"
#include <iostream>
#include <thread>

class TestClass
{
public:
	TestClass()
	{
		_x = 99;
	}

	~TestClass()
	{
	}

	TestClass(const TestClass& testClass)
	{
		_x = testClass._x;
	}

	void operator = (const TestClass& testClass)
	{
		_x = testClass._x;
	}

private:
	int _x;
};

void g(const TestClass& testclass)
{

}

void f(int i, const std::string& value)
{

}

class X
{
public:
	void DoSomething(float value)
	{
		_x = value;
	}

private:
	float _x;
};

BEGIN_TEST(Ch2_PassingArguments)
	char buffer[1024];
	//std::thread t(f, 3, buffer);//main thread can finish before the pointer is accessed.
	std::thread t(f, 3, std::string(buffer)); //using std::string avoids dangling pointer.
	t.detach();

	std::string test = "99";
	std::string& test2 = test;
	std::thread t1(f, 3, test);
	t1.detach();

	TestClass testClass;
	std::thread t2(g, testClass);
	t2.detach();

	std::thread t3(g, std::ref(testClass)); //doing a real passing by reference value
	t3.detach();

	X myObject;
	std::thread t4(&X::DoSomething, &myObject, 3.0f); //This code will invoke my_x.do_lengthy_work() on the new thread
	t4.detach();

END_TEST()

//int main(){MainExample(); return 0;}
