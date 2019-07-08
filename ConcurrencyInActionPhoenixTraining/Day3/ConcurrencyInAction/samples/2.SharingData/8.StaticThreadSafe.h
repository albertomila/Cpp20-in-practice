#pragma once
#include "stdafx.h"

namespace Ex14
{
	class StaticClass
	{
	public:
		StaticClass()
			:_data(99)
		{
		}

	private:
		int _data;
	};

	StaticClass& GetInstance()
	{
		//static initialization is thread safe in C++11, only one thread initializes the static instance.
		static StaticClass instance;
		return instance;
	}

	void ThreadA()
	{
		StaticClass& instance = GetInstance();
	}

	void ThreadB()
	{
		StaticClass& instance = GetInstance();
	}

	BEGIN_TEST(Ex14_StaticThreadSafe)
		std::thread threadA(ThreadA);
		std::thread threadB(ThreadB);

		threadA.join();
		threadB.join();
	END_TEST()
}