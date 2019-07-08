#include "stdafx.h"
#include <iostream>
#include <thread>
#include <chrono>

class thread_guard
{
	std::thread& _t;
public:

	explicit thread_guard(std::thread& t)
		:_t(t)
	{
	}

	~thread_guard()
	{
		if (_t.joinable())
		{
			_t.join();
		}
	}
	thread_guard(thread_guard const&) = delete;
	thread_guard& operator=(thread_guard const&) = delete;
};





void DoSomethingInCurrentThread()
{
}

struct StructTest
{
	void operator()() const
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << "1";
		}
	}
};

BEGIN_TEST(Ch2_JoinAllCases)
	//function version
	StructTest myFunc;
	std::thread t(myFunc);

	try
	{
		DoSomethingInCurrentThread();
	}
	catch (...)
	{
		t.join();
		throw;
	}

	t.join();

	//class version
	std::thread t2(myFunc);
	thread_guard tg(t2);
	DoSomethingInCurrentThread();

END_TEST()

//int main(){MainExample(); return 0;}
