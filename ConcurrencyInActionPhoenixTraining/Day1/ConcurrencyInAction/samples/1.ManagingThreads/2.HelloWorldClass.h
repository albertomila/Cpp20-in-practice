#include "stdafx.h"
#include <iostream>
#include <thread>
#include <chrono>


namespace Ex2
{
	class ThreadClass
	{
	public:
		void operator()() const
		{
			sleep(100);
			std::cout << "ThreadClass" << std::endl;
		}
	};

	void ThreadFoo()
	{
		std::cout << "ThreadFoo" << std::endl;
	}

	BEGIN_TEST(Ex2_HelloWorldClass)
		std::thread threadFunction(ThreadFoo);
		threadFunction.join();

		//It doesn't compile. Function "ThreadClass" not found
		//std::thread threadClassAsFooError( ThreadClass() );
		//threadClassAsFooError.join();

		//Solution, double parenthesis or bracets
		std::thread threadClass1((ThreadClass()));
		threadClass1.join();

		std::thread threadClass2{ ThreadClass() };
		threadClass2.join();
	END_TEST()

		/////////////////////////////////////////////////////////////////////


	std::thread FooInitThread()
	{
		ThreadClass f;
		std::thread my_thread(f);
		return my_thread;
	}

	BEGIN_TEST(Ex2_HelloWorldClass2)
		std::thread thread(FooInitThread());
		thread.join();
	END_TEST()


		/////////////////////////////////////////////////////////////////////
		void ThreadPass1()
	{
		for (int i = 0; i < 3; ++i)
		{
			sleep(1000);
			std::cout << "Ex2_ThreadPass1" << std::endl;
		}
	}

	void ThreadPass2()
	{
		for (int i = 0; i < 3; ++i)
		{
			sleep(1000);
			std::cout << "Ex2_ThreadPass2" << std::endl;
		}
	}

	BEGIN_TEST(Ex2_HelloWorldLamda)

		//It executes a sequence of threads, one after other.
		//When thread1 is finished, it starts thread2 and so on.
		std::thread sequenceThreads
		{[]
			{
				ThreadPass1();
				ThreadPass2();
			}
		};
		sequenceThreads.detach();

	END_TEST()


	class ClassMethod
	{
	public:
		void Method()
		{
			sleep(1000);
			std::cout << "Ex2_ClassMethod" << std::endl;
		}
	};

	BEGIN_TEST(Ex2_HelloWorldClassMethod)
		ClassMethod helloWorldClassMethod;
		std::thread threadClassMethod(&ClassMethod::Method, &helloWorldClassMethod);
		threadClassMethod.join();
	END_TEST()
}