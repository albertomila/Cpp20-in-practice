#include "stdafx.h"
#include <future>
#include <iostream>

class AsyncThread
{
public:
	AsyncThread()
	{
	}

	AsyncThread(const AsyncThread& asyncThread)
	{
	}

	int Foo(int arg1, const std::string& arg2)
	{
		return arg1 + 1;
	}
};

class AsyncThreadEmpty
{
public:
	AsyncThreadEmpty()
	{
	}

	AsyncThreadEmpty(const AsyncThreadEmpty& asyncThread)
	{
	}

	int operator()(int arg)
	{
		return arg + 1;
	}
};

class AsyncThreadMoveOnly
{
public:
	AsyncThreadMoveOnly() {}
	AsyncThreadMoveOnly(AsyncThreadMoveOnly&& moveOnly)
	{
		int x = 0;
		++x;
	}
	AsyncThreadMoveOnly& operator = (AsyncThreadMoveOnly&& moveOnly)
	{
		int x = 0;
		++x;

		return moveOnly;
	}
	void operator() ()
	{
		int x = 0;
		++x;
	}


	//deleted
	AsyncThreadMoveOnly(const AsyncThreadMoveOnly& moveOnly)
	{
		int x = 0;
		++x;
	}
	AsyncThreadMoveOnly& operator = (const AsyncThreadMoveOnly& moveOnly)
	{
		int x = 0;
		++x;
		return *this;
	}
};


int find_the_answer_to_ltuae()
{
	return 0;
}

void do_other_stuff()
{
	sleep(1000);
}


BEGIN_TEST(Ch4_Future)
	//example 1
	std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
	do_other_stuff();
	std::cout << "The answer is " << the_answer.get() << std::endl;

	//example 2: passing arguments
	AsyncThread asyncThread;
	std::future<int> result1 = std::async(&AsyncThread::Foo, &asyncThread, 5, "Hello"); //ref to object, no copy
	std::future<int> result2 = std::async(&AsyncThread::Foo, asyncThread, 5, "Hello"); //copy of asyncThread

	//example 4: std::ref
	AsyncThreadEmpty asyncThreadEmpty;
	std::future<int> result3 = std::async(asyncThreadEmpty, 99); //copy of AsyncThreadEmpty
	std::future<int> result4 = std::async(std::ref(asyncThreadEmpty), 99); //ref to object, no copy

	//example 5
	AsyncThreadMoveOnly asyncThreadMoveOnly;
	std::future<void> result5 = std::async(AsyncThreadMoveOnly());
	std::future<void> result6 = std::async(std::move(asyncThreadMoveOnly));

	//std::launch::deferred, put off until either wait() or get(), it may never actally run.
	//std::launch::async, indicates that the funcion ust be run on its own thread
	//(std::launch::deferred | std::launch::async) is the optyion by default
	AsyncThreadMoveOnly asyncThreadMoveOnly2;
	std::future<void> result7 = std::async(std::launch::deferred, std::move(asyncThreadMoveOnly2));
	result7.wait();//invoke deferred function

END_TEST()
