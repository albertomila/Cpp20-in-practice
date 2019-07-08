#pragma once
#include "stdafx.h"
#include <vector>

namespace Ex13
{
	class ItemFlag
	{
	private:
		std::once_flag _initFlag;

	private:
		void DoSomethingUnique()
		{
		}

		void DoSomethingGeneral()
		{
		}

	public:
		ItemFlag()
		{
		}

		void DoSomething()
		{
			//this call might not be called due to the call_once in DoSomethingElse()
			std::call_once(_initFlag, &ItemFlag::DoSomethingUnique, this);

			DoSomethingGeneral();
		}

		void DoSomethingElse()
		{
			//this call might not be called due to the call_once in DoSomething()
			std::call_once(_initFlag, &ItemFlag::DoSomethingUnique, this);

			DoSomethingGeneral();
		}
	};


	void ThreadA(ItemFlag& item1)
	{
		while (true)
		{
			std::cout << "ThreadA" << "\n" << std::endl;

			item1.DoSomething();
		}
	}

	void ThreadB(ItemFlag& item1)
	{
		while (true)
		{
			std::cout << "ThreadB" << "\n" << std::endl;
			item1.DoSomethingElse();
		}
	}


	BEGIN_TEST(Ex13_OnceFlag)
		ItemFlag item;
		std::thread threadA(ThreadA, std::ref(item));
		std::thread threadB(ThreadB, std::ref(item));

		threadA.join();
		threadB.join();

	END_TEST()
}