#pragma once
#include "stdafx.h"
#include <vector>

namespace Ex6
{
	void Thread()
	{
	}

	BEGIN_TEST(Ex6_MultipleThreads)
		std::vector<std::thread> threads;
		for (int i = 0; i < 20; ++i)
		{
			threads.push_back(std::thread(Thread));
		}

		for (int i = 0; i < 20; ++i)
		{
			threads[i].join();
		}


		//or
		//std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
	END_TEST()

	void ThreadTimer(int delay)
	{
		sleep(delay * 100);
		sleep(1000);
		std::cout << "Thread id:" << std::this_thread::get_id() << std::endl;
	}


	//Asks for threads depending on the hardware threads
	BEGIN_TEST(Ex6_MultipleThreadsMaxAvailable)
		std::thread::id master_thread;
		std::cout << "master thread id: " << master_thread << std::endl;

		int threadsToExecute = 20;
		while (threadsToExecute > 0)
		{
			std::vector<std::thread> threads;
			int availableThreads = std::thread::hardware_concurrency();
			std::cout << "availableThreads: " << availableThreads << std::endl;
			for (int i = 0; i < availableThreads && threadsToExecute > 0; ++i)
			{
				--threadsToExecute;
				threads.push_back(std::thread(ThreadTimer, i));
			}

			//Wait for all threads finished
			for (int i = 0; i < static_cast<int>(threads.size()); ++i)
			{
				threads[i].join();
			}
			std::cout << "------------THREADS FINISHED" << std::endl;
		}

		std::cout << "------------ALL THREADS FINISHED" << std::endl;
	END_TEST()
}