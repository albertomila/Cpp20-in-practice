#include "stdafx.h"
#include <mutex>
#include <thread>
#include <list>


class DebugTask
{
	int _id = 0;
public:
	DebugTask(int id_)
		:_id(id_)
	{
	}
	void operator()() const
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << _id << ",";
		}
	}
};

const int MAX_THREADS = 10;

BEGIN_TEST(Ch8_DebuggingThreads)
	std::list<std::thread*> threads;

	for (int i = 0; i < MAX_THREADS; ++i)
	{
		std::thread* th = new std::thread(DebugTask(i));
		threads.push_back(th);
	}

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "m,";
	}

	for (std::thread* th : threads)
	{
		th->join();
	}

	std::cout << "thread main" << std::endl;

END_TEST()