#pragma once
#include "stdafx.h"
#include <mutex>
#include <vector>


namespace Ex7
{
	std::vector<int> _list;
	std::mutex _mutex;
	static const int SLEEP_TIME = 30;

	inline void AddToList(int value)
	{
		std::lock_guard<std::mutex> guard(_mutex);
		_list.push_back(value);
	}

	inline void Remove(int valueToFind)
	{
		std::lock_guard<std::mutex> guard(_mutex);

		std::vector<int>::iterator it = std::find(_list.begin(), _list.end(), valueToFind);
		if (it != _list.end())
		{
			_list.erase(it);
		}
	}

	inline void ThreadAdd()
	{
		while (true)
		{
			sleep(SLEEP_TIME);
			int value = rand() % 10;
			AddToList(value);
		}
	}

	inline void ThreadRemove()
	{
		while (true)
		{
			sleep(SLEEP_TIME);
			int value = rand() % 10;
			Remove(value);
		}
	}

	inline void ThreadPrint()
	{
		while (true)
		{
			sleep(SLEEP_TIME);
			std::lock_guard<std::mutex> guard(_mutex);
			if (!_list.empty())
			{
				for (int value : _list)
				{
					std::cout << value << ",";
				}
				std::cout << endl;
			}
		}
	}

	BEGIN_TEST(Ex7_Mutex)

		std::thread thread1(ThreadAdd);
		std::thread thread2(ThreadRemove);
		std::thread thread3(ThreadPrint);
		thread1.join();
		thread2.join();
		thread3.join();

	END_TEST()
}