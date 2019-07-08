#pragma once
#include "stdafx.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace Ex3
{
	void ThreadFoo()
	{

	}

	void DoSomething()
	{

	}

	BEGIN_TEST(Ex3_HandleJoinCases)
		std::thread joinCasesThread(ThreadFoo);

		try
		{
			DoSomething();
		}
		catch (...)
		{
			joinCasesThread.join();
			throw;
		}

		joinCasesThread.join();
	END_TEST()


	/////////////////////////////////////////////////////

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

	BEGIN_TEST(Ex3_HandleJoinCases2)
		std::thread joinCasesThread(ThreadFoo);
		thread_guard safeThread(joinCasesThread);

		try
		{
			DoSomething();
		}
		catch (...)
		{
			throw;
		}

	END_TEST()

	BEGIN_TEST(Ex3_HandleDetach)
		std::thread detachThread(ThreadFoo);

		//when thread is finished it doesn't call std::terminate()
		//no longer possible to wait for the thread to complete
		//it can't be joined again, if join() is called it crashes
		//oriented to long-running tasks, monitoring, cleaning and such
		//When you don't care waiting for the new thread to finish
		detachThread.detach();

	END_TEST()
}